#include<stdio.h>
#include<string.h>
#include<error.h>
#include<errno.h>
#include<sys/epoll.h>
#include <sys/types.h>
#include<fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
#include<cstring>
#include<stdlib.h>
#include<assert.h>

#define BUFFERSIZE 10
#define MAX_EVENT_NUM 100

#define IP_ADDR "127.0.0.1"
#define IP_PORT 8888

int setNoBlacking(int fd){
    int old_opt=fcntl(fd,F_GETFL); //fcntl改变文件描述符的状态，
    int new_opt=old_opt|O_NONBLOCK;
    fcntl(fd,F_SETFL,new_opt);
    printf("set balcking successed\n");
    return old_opt;
}
//将文件描述符注册到epfd中，并设置是否支持et;
void addFd(int epfd,int sockfd,bool et) {
    epoll_event ev;
    ev.data.fd=sockfd;
    ev.events=EPOLLIN;
    printf("register :%d\n",sockfd);
    if(et){
        ev.events|=EPOLLET;
        int epctl_fd=epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
        if(epctl_fd<0){
            printf("registerd failure\n");
            return;
        }else {
            printf("epoll_ctl_succedded:%d\n",epctl_fd);
        } 
    }
    setNoBlacking(sockfd);
}

void ETWorkModel(int epfd,int sockfd,int evNumber,epoll_event *events) {
    char BUFF[BUFFERSIZE];
    printf("evNuber:%d\n",evNumber);
    for(int i=0;i<evNumber;i++){
        int evfd=events[i].data.fd;
        if(evfd==sockfd){
            struct sockaddr_in sockaddr;
            socklen_t sockaddrsize=sizeof(sockaddr);
            int acceptfd=accept(evfd,(struct sockaddr*)&sockaddr,&sockaddrsize);
            if(acceptfd<0){
                continue;
            }else{
                printf("et_model\n");
                addFd(epfd,acceptfd,true);
            }
        }else if(events[i].events&EPOLLIN){
            //已经注册过的fd;
            printf("worked in ET model\n");
            while(1){
                memset(BUFF,'\0',BUFFERSIZE);
                int ret=recv(evfd,BUFF,sizeof(BUFF)-1,0);
                printf("recv_ret:%d\n",ret);
                if(ret<0){
                    if(errno==EAGAIN| errno==EWOULDBLOCK){
                        printf("read latter\n");
                        break;
                    }else{
                        close(sockfd);
                        break;
                    }
                }else if(ret==0) {
                    printf("client offline\n");
                    close(sockfd);
                }else{
                    printf("get data:%s",BUFF);
                }
            }
        }else{
            printf("other things happends\n");
        }
    }
}

void LTWorkModel(int epfd,int sockfd,int evNumber,epoll_event *events) {
    char BUFF[BUFFERSIZE];
    printf("evNuber:%d\n",evNumber);
    for (size_t i = 0; i < evNumber; i++)
    {
        int evfd=events[i].data.fd;
        if(evfd==sockfd){
            printf("nihao____\n");
            struct sockaddr_in sockaddr;
            socklen_t len=sizeof(sockaddr);
            int accepfd=accept(sockfd,(struct sockaddr*)&sockaddr,&len);
            if(accepfd<0){
                printf("accept error:%s %d",strerror(errno),errno);
                break;
            }else{
                printf("welcome client:%d\n",sockfd);
            }
            addFd(epfd,accepfd,false);
        }else {
            printf("epol\n");
            bzero(BUFF,sizeof(BUFF));
            int recvsize=recv(sockfd,BUFF,sizeof(BUFF)-1,0);
            if(recvsize<0){
                if(errno==EAGAIN|errno==EWOULDBLOCK){
                    continue;
                }
                close(sockfd);
                continue;
            }else if(recvsize==0){
                close(sockfd);
                break;
            }else{
                printf("recvdata:%s %d",strerror(errno),errno);
            }
            
        }
    }
}
int main(int argc,char *argv[]){
    printf("mian start_\n");
    int port=IP_PORT;
    struct sockaddr_in sockaddr_;
    
    bzero(&sockaddr_,sizeof(sockaddr_));
    sockaddr_.sin_family=AF_INET;
    if (inet_pton(AF_INET, IP_ADDR, &sockaddr_.sin_addr) <= 0) {
      printf("inet_pton Error: %s (errno: %d)\n", strerror(errno), errno);
      exit(0);
    }
    
    // sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr_.sin_port=htons(port);
    socklen_t sock_len=sizeof(sockaddr_);

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    assert(sockfd!=-1);

    int bindfd=bind(sockfd,(struct sockaddr*)&sockaddr_,sock_len);
    if(bindfd<-1){
        printf("bindfd=%d",bindfd);
    }else{
        printf("bind successed\n");
    }

    int lisfd=listen(sockfd,5);
    assert(lisfd!=-1);
    int epfd=epoll_create(5);
    epoll_event epl_event[MAX_EVENT_NUM]; 
    addFd(epfd,sockfd,true); //注册事件，并设置边缘触发模式
    while(1){
        printf("epoll_waiting\n");
        int evtNum=epoll_wait(epfd,epl_event,MAX_EVENT_NUM,-1);
        printf("evtNum=%d\n",evtNum);
        if(evtNum<0){
            printf("epoll failured\n");
            break;
        }else if(evtNum==0){
            printf("not client connect\n");
        }
        ETWorkModel(epfd,sockfd,evtNum,epl_event);
        // LTWorkModel(epfd,sockfd,evtNum,epl_event);
    }
    close(sockfd);
    return 0;
}

