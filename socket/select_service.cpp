#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

#define MAXSIZE 1024
#define IP_ADDR "127.0.0.1"
#define IP_PORT 8888

int main(){
    int sock_fd=-1,accept_fd=-1;
    sockaddr_in sock_add;

    if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("socket error :%s %d",strerror(errno),errno);
        exit(0);
    }
    memset(&sock_add,0,sizeof(sock_add));
    sock_add.sin_family=AF_INET;
    sock_add.sin_addr.s_addr=htonl(INADDR_ANY);
    sock_add.sin_port=htons(IP_PORT);

    if(bind(sock_fd,(const sockaddr *)&sock_add,sizeof(sock_add))<0){
        printf("bind error :%s %d",strerror(errno),errno);
        exit(0);
    }
    if(listen(sock_fd,5)<0){
        printf("listen error :%s %d",strerror(errno),errno);
        exit(0);
    }
    char buf[MAXSIZE],msg[MAXSIZE];
    fd_set readfd,writefd,exceptfd;
    FD_ZERO(&readfd);
    FD_ZERO(&writefd);
    FD_ZERO(&exceptfd);
    int canusefd[MAXSIZE],index=0,maxfd=-1;
    memset(canusefd,-1,sizeof(MAXSIZE));
    canusefd[index]=maxfd=sock_fd;

    printf("waiting client request\n");

    while(1){
        //将所有的文件描述符加入 刻度事件中
        for(int i=0;i<=index;i++){
           FD_SET(canusefd[i],&readfd);
        }
        int ncount=select(maxfd+1,&readfd,&writefd,NULL,0);
        printf("监听到的事件数量为：%d\n",ncount);
        for(int i=0;i<MAXSIZE;i++){
            if(ncount==0){
                break;
            }
            std::cout<<"test1\n";
            if(!FD_ISSET(canusefd[i],&readfd)){
                continue;//不在监听事件中则跳过；
            }
            //处理监听到的事件
            std::cout<<"test2\n";
            if(canusefd[i]==sock_fd){ //监听到客户端连接事件

                ncount--;
                if((accept_fd=accept(sock_fd,(sockaddr*)NULL,NULL))<0){
                    printf("accept error:%s %d",strerror(errno),errno);
                }
                std::cout<<"test3\n";
                //将新连接的文件描述符加入canusefd数组中
                for(int j=0;j<MAXSIZE;j++){
                    if(canusefd[j]==-1){
                        std::cout<<"test5\n";
                        canusefd[j]=accept_fd;
                        maxfd=maxfd<accept_fd?accept_fd:maxfd;
                        index=index<j?j:index;
                        std::cout<<"test6\n";
                        break;
                    }
                }
                std::cout<<"test7\n";
            }else{
                std::cout<<"test4\n";
                ncount--;
                memset(msg,0,sizeof(msg));
                int recvsize=-1;
                if((recvsize=read(canusefd[i],msg,sizeof(msg)))<0){
                    printf("read error :%s %d",strerror(errno),errno);
                    continue;
                }else if(recvsize==0){
                    printf("elient discount\n");
                    if(maxfd==canusefd[i]){
                        maxfd--;
                    }
                    if(index==i){
                        index--;
                    }
                    close(canusefd[i]);
                    FD_CLR(canusefd[i],&readfd);
                    canusefd[i]=-1;
                    continue;
                }else{
                    printf("recved msg:%s",msg);
                    for(int i=0;msg[i]!='\0';i++){
                        msg[i]=toupper(msg[i]);
                    }
                    if(write(canusefd[i],msg,strlen(msg)+1)<0){
                        printf("write error:%s %d",strerror(errno),errno);
                    }
                }
            }
        }

    }
    close(sock_fd);
    return 0;
}