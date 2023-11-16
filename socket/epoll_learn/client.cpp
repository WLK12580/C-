#include<iostream>
#include<sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<errno.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888
#define balcklog 4
#define MAXLINE 4096
#define IP_ADDR "127.0.0.1"
void process_read_write(int client_fd);
int main(int argc,char *argv[]) {
  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0) {
    perror("client_socket_error");
    return -1;
  }
  struct sockaddr_in sockaddr;
  bzero(&sockaddr,sizeof(sockaddr));
  sockaddr.sin_family=AF_INET;
  
  if(inet_pton(AF_INET,IP_ADDR,&sockaddr.sin_addr)<0){
    perror("ipton error\n");
    return -1;
  }
  sockaddr.sin_port=htons(PORT);
  int conn_fd=connect(client_fd,(struct sockaddr*)&sockaddr,(socklen_t)sizeof(sockaddr));
  if(conn_fd<0){
    perror("client_connect_error\n");
    return -1;
  }
  process_read_write(client_fd);
  close(client_fd);
  return 0;
}

void process_read_write(int client_fd) {
  char send_buffer[1024];
  for (;;) {
    size_t read_len = read(0, send_buffer, sizeof(send_buffer));
    if (read_len > 0) {
      write(client_fd, send_buffer, read_len);
      read_len = read(client_fd, send_buffer, 1024);
      write(1, send_buffer, read_len);
    }
    char msg[1024];
    memset(msg, 0, 102);
    int recv_len = 0;
    if (recv_len = read(client_fd, msg, sizeof(msg)) < 0) {
      printf("read Error: %s (errno: %d)\n", strerror(errno), errno);
    } else if (recv_len == 0) {
      printf("Service Close!\n");
    } else {
      printf("Server return: %s\n", msg);
    }
}}