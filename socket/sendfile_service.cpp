#include <assert.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <syslog.h>

#include <iostream>
#include <memory>

#include "epoll_header.hpp"
#define MAXSIZE 1024
int main(int argc, char *argv[]) {
  char msg[MAXSIZE];
  FILE *filefd;
  int epollfd = -1, epoll_ncount = 0, acceptfd = -1;
  std::shared_ptr<SocketCreate> socker_ptr = std::make_shared<SocketCreate>();
  if (socker_ptr->Socket()) {
    socker_ptr->Bind();
    socker_ptr->Listen();
  }
  if ((epollfd = epoll_create(MAXSIZE)) < 0) { //创建epoll内核事件表，MAXSIZE表示内核时间表的大小
    printf("epoll_create Error: %s (errno: %d)\n", strerror(errno), errno);
    exit(-1);
  }
  struct epoll_event ev, eventbuff[MAXSIZE]; 
  ev.events = EPOLLIN;   //EPOLLIN事件则只有当对端有数据写入时才会触发，所以触发一次后需要不断读取所有数据直到读完EAGAIN为止。否则剩下的数据只有在下次对端有写入时才能一起取出来了。                                                     // 文件描述符刻度
  ev.data.fd = socker_ptr->GetSocketfd();                                       // socket文件描述符
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, socker_ptr->GetSocketfd(), &ev) < 0) {  // epoll控制操作
    printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
    exit(-1);
  }
  printf("======waiting for client's request======\n");

  while (1) {
    const char *filename = argv[1];
    char filedata[1024];
    int filefd = open(filename, O_RDONLY);
    assert(filefd > 0);
    struct stat stat_buf;

    if ((epoll_ncount = epoll_wait(epollfd, eventbuff, MAXSIZE, -1)) <
        0) {  // 返回值：成功时，epoll_wait（）返回为请求的I /
              // O准备就绪的文件描述符的数目；如果在请求的超时毫秒内没有文件描述符准备就绪，则返回零。发生错误时，epoll_wait（）返回-1并正确设置errno。
      printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
      exit(-1);
    } else if (epoll_ncount == 0) {
      printf("timeout,no data connect\n");
      exit(-1);
    } else {
      for (int i = 0; i < epoll_ncount; i++) { //遍历就绪事件
        int epoll_recved_fd = eventbuff[i].data.fd; 
        if (epoll_recved_fd == socker_ptr->GetSocketfd()) {
          // 处理新连接的用户
          if ((acceptfd = accept(socker_ptr->GetSocketfd(), (struct sockaddr *)NULL, NULL)) < 0) {
            printf("accept Error: %s (errno: %d)\n", strerror(errno), errno);
            // continue; //接收失败链接下一个
          } else {
            printf("Client[%d], welcome!\n", acceptfd);  // 新用户添加
          }
          // 向epoll中添加新用户
          ev.events = EPOLLIN;
          ev.data.fd = acceptfd;
          if (epoll_ctl(epollfd, EPOLL_CTL_ADD, acceptfd, &ev) < 0)  // 新用户注册
          {
            printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
            exit(-1);
          }
        } else {
          // 已经连接的直接收发数据
          memset(msg, 0, sizeof(msg));
          int recvsize = 0;
          // std::cout<<"read_write\n";
          if ((recvsize = read(epoll_recved_fd, msg, sizeof(msg))) < 0) {
            printf("read Error: %s (errno: %d)\n", strerror(errno), errno);
            continue;
          } else if (recvsize == 0) {
            printf("not received data\n");
            epoll_ctl(epollfd, EPOLL_CTL_DEL, epoll_recved_fd, NULL);  // 说明链接放断开了链接
            close(epoll_recved_fd);                                    // 关闭相关的文件描述符
            continue;
          } else {
            int filefd=open(filename,O_RDONLY);
            struct stat stat_buf;
            fstat(filefd,&stat_buf);
            sendfile(epoll_recved_fd,filefd,NULL,stat_buf.st_size);
            printf("send sucessed\n");
          }
        }
      }
    }
  }
  close(epollfd);
  close(socker_ptr->GetSocketfd());
  std::cout << "service_close\n";
  return 0;
}