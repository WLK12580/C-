#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#define PORT 8888
#define balcklog 4
#define MAXLINE 4096
void getDataFromClient(int client_fd);
int main(){
    int service_fd;
    struct sockaddr_in service_add; //服务端地址结构体
    //建立socket
    service_fd=socket(AF_INET,SOCK_STREAM,0);
    if(service_fd<0){
        std::cout<<"socket error"<<std::endl;
        return -1;
    }
    bzero(&service_add,sizeof(service_add));

    service_add.sin_family=AF_INET;
    service_add.sin_addr.s_addr=htonl(INADDR_ANY);
    service_add.sin_port=htons(PORT);
    int bind_fd=bind(service_fd,(sockaddr*)&service_add,sizeof(service_add));
    if(bind_fd<0){
        std::cout<<"bind error\n";
        return -1;
    }
    int listen_fd=listen(service_fd,balcklog);
    if(listen_fd<0){
        std::cout<<"listen error\n";
        return -1;
    }
    struct sockaddr_in client_add;
    for(;;){
        socklen_t addlen=sizeof(sockaddr);
        std::cout<<"test02\n";
        int accept_fd=accept(service_fd,(struct sockaddr*)&client_add,&addlen);
        if(accept_fd<0){
            std::cout<<"accept error\n";
            return -1;
        }
        std::cout<<"test01\n";
        int pro=fork();
        if(pro==0){
            close(service_fd);
            getDataFromClient(accept_fd);

        }else if(pro>0){
            close(accept_fd);
        }
    }
}

void getDataFromClient(int client_fd){
    char buff[MAXLINE];
    size_t n;
loop:
    while(n=read(client_fd,buff,sizeof(buff))>0){
        std::cout<<"buff="<<buff<<std::endl;
    }
    if(n<0 && errno==EINTR){
        goto loop;
    }
    if(n<0){
        perror("endl");
    }
    if(write(client_fd,buff,sizeof(buff)+1)<0){
        printf("socket Error: %s (errno: %d)\n", strerror(errno), errno);
		// exit(0);
    }
}