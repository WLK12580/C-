#include <memory>

#include "epoll_header.hpp"
#define MAXSIZE 1024
int main() {
  char msg[MAXSIZE];
  FILE *filefd;
  int epollfd = -1, epoll_ncount = 0, acceptfd = -1;
  std::shared_ptr<SocketCreate> socker_ptr = std::make_shared<SocketCreate>();
  if (socker_ptr->Socket()) {
    socker_ptr->Bind();
    socker_ptr->Listen();
  }
  if ((epollfd = epoll_create(MAXSIZE)) < 0) {
    printf("epoll_create Error: %s (errno: %d)\n", strerror(errno), errno);
    exit(-1);
  }
  struct epoll_event ev, eventbuff[MAXSIZE];
  ev.events = EPOLLIN;
  ev.data.fd = socker_ptr->GetSocketfd();
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, socker_ptr->GetSocketfd(), &ev) < 0) {
    printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
    exit(-1);
  }
  printf("======waiting for client's request======\n");
  while (1) {;
    if ((epoll_ncount = epoll_wait(epollfd, eventbuff, MAXSIZE, -1)) < 0) {
      printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
      exit(-1);
    } else if (epoll_ncount == 0) {
      printf("timeout,no data connect\n");
      exit(-1);
    } else {
      for (int i = 0; i < epoll_ncount; i++) {
        int epoll_recved_fd = eventbuff[i].data.fd;
        if (epoll_recved_fd == socker_ptr->GetSocketfd()) {
          // 处理新连接的用户
          if ((acceptfd = accept(socker_ptr->GetSocketfd(), (struct sockaddr*)NULL, NULL)) < 0) {
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
            epoll_ctl(epollfd,EPOLL_CTL_DEL,epoll_recved_fd,NULL); //说明链接放断开了链接
            close(epoll_recved_fd); //关闭相关的文件描述符
            continue;
          } else {
            printf("recved_data=%s", msg);
            for (int i = 0; msg[i] != '\0'; i++) {
              msg[i] = toupper(msg[i]);
            }
            if (write(epoll_recved_fd, msg, strlen(msg) + 1) < 0) {
              printf("write Error: %s (errno: %d)\n", strerror(errno), errno);
            }
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