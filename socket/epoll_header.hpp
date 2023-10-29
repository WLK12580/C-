#include<iostream>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <netinet/in.h>

class IPPort {
public:
  std::string GetIP() { return IP; }
  int GetPort() { return PORT; }

 private:
  std::string IP = "127.0.0.1";
  int PORT = 8888;
};
class SocketCreate : public IPPort {
 public:
  bool Socket();
  bool Bind();
  bool Listen();
  bool Accept();
  int GetSocketfd();
  int GetAcceptfd();
  IPPort ipport;

 private:
 int socket_fd=-1;
 int accept_fd=-1;

 struct sockaddr_in st_sersock;
};
bool SocketCreate::Socket(){
  if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0){
    printf("SocketCreate Error: %s (errno: %d)\n", strerror(errno), errno);
    return false;
  }else{
    std::cout<<"socket_fd="<<socket_fd<<std::endl;
    return true;
  }
} 
bool SocketCreate::Bind(){
  memset(&st_sersock,0,sizeof(st_sersock));
  st_sersock.sin_family=AF_INET;
  st_sersock.sin_addr.s_addr=htonl(INADDR_ANY);
  st_sersock.sin_port=htons(ipport.GetPort());
  std::cout<<"bind_socket_fd="<<socket_fd<<std::endl;
  if(bind(socket_fd,(struct sockaddr*)&st_sersock,sizeof(st_sersock))<0){
    printf("bind Error: %s (errno: %d)\n", strerror(errno), errno);
    return false;
  }else{
    std::cout<<"bind successed!\n";
    return true;
  }
}
bool SocketCreate::Listen(){
  if(listen(socket_fd,10)<0){
    printf("listen Error: %s (errno: %d)\n", strerror(errno), errno);
		return false;
  }else{
    std::cout<<"listen successed!\n";
    return true;
  }
}
bool SocketCreate::Accept(){
  if(accept(socket_fd,(struct sockaddr*)NULL,NULL)){
    printf("accept Error: %s (errno: %d)\n", strerror(errno), errno);
    return false;
  }else{
    std::cout<<"accept successed!\n";
    return true;
  }
}
int SocketCreate::GetSocketfd(){
  return socket_fd;
}
int SocketCreate::GetAcceptfd(){
  return accept_fd;
}