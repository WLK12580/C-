/*
服务端：
socket()
bind()
listen()
epoll_create()  高并发poll模式
epoll_ctl()
epoll_wait()
accept()
read() 或 recv()等
write() 或 send()等
close()

客户端：
socket()
connect()
write() 或 send()等
read() 或 recv()等
close()

epoll是增强版的poll，可以看做event poll，通过红黑树和内核维护的等待队列等结构实现的事件触发等机制实现的高并发，解决了select和poll未能解决的遍历所有fd来查找响应的缺陷，同时可以通过非阻塞IO模式实现更高的服务性能。

/proc/sys/fs/epoll/max_user_watches:这个文件中的值表示用户能注册到epoll实例中的最大文件描述符的数量限制(也就是硬件本身支持的最大数量限制)

关键函数
int epoll_create(int size);	//创建一个epoll实例(本质是红黑树),也占用个文件描述符，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。
				//size用来告诉内核这个监听的数目一共有多大，自从Linux 2.6.8开始，size参数被忽略，但是依然要大于0。

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)；
	将监听的文件描述符添加到epoll实例中，实例代码为将标准输入文件描述符添加到epoll中
	第一个参数是epoll_create()的返回值，
	第二个参数表示动作，用三个宏来表示：
		EPOLL_CTL_ADD：注册新的fd到epfd中；
		EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
		EPOLL_CTL_DEL：从epfd中删除一个fd；
	第三个参数是需要监听的fd，
	第四个参数是告诉内核需要监听什么事，struct epoll_event结构如下：
		struct epoll_event {
			__uint32_t events; // Epoll events 
			epoll_data_t data; // User data variable 
		};
		events可以是以下几个宏的集合(常用的IN/OUT/ERR/ET)：
			EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
			EPOLLOUT：表示对应的文件描述符可以写；
			EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
			EPOLLERR：表示对应的文件描述符发生错误；
			EPOLLHUP：表示对应的文件描述符被挂断；
			EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
			EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。
		epoll_data_t联合体定义如下：(注意是联合体)
			typedef union epoll_data
			{
			  void *ptr;		//可以传递任意类型数据，常用来传 回调函数
			  int fd;		//可以直接传递客户端的fd
			  uint32_t u32;
			  uint64_t u64;
			} epoll_data_t;


int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
等待epoll事件从epoll实例中发生， 并返回事件总数以及传出对应文件描述符
	参数events用来从内核得到事件的集合，
	参数maxevents表示每次能处理的最大事件数，告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，
	参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。


注意：epoll的两种触发模式：
	边沿触发vs水平触发
	epoll事件有两种模型，边沿触发：edge-triggered (ET)， 水平触发：level-triggered (LT)
	水平触发(level-triggered),是epoll的默认模式
		socket接收缓冲区不为空 有数据可读 读事件一直触发
		socket发送缓冲区不满 可以继续写入数据 写事件一直触发
	边沿触发(edge-triggered)
		socket的接收缓冲区状态变化时触发读事件，即空的接收缓冲区刚接收到数据时触发读事件
		socket的发送缓冲区状态变化时触发写事件，即满的缓冲区刚空出空间时触发读事件
	边沿触发仅触发一次，水平触发会一直触发。
	开源库:libevent 采用水平触发， nginx 采用边沿触发
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <ctype.h>
#include <sys/epoll.h>	//epoll头文件

#define MAXSIZE 1024
#define IP_ADDR "127.0.0.1"
#define IP_PORT 8888

int main()
{
	int i_listenfd, i_connfd;
	struct sockaddr_in st_sersock;
	char msg[MAXSIZE];
	int nrecvSize = 0;

	struct epoll_event ev, events[MAXSIZE];
	int epfd, nCounts;	//epfd:epoll实例句柄, nCounts:epoll_wait返回值

	if((i_listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)	//建立socket套接字
	{
		printf("socket Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&st_sersock, 0, sizeof(st_sersock));
	st_sersock.sin_family = AF_INET;  //IPv4协议
	st_sersock.sin_addr.s_addr = htonl(INADDR_ANY);	//INADDR_ANY转换过来就是0.0.0.0，泛指本机的意思，也就是表示本机的所有IP，因为有些机子不止一块网卡，多网卡的情况下，这个就表示所有网卡ip地址的意思。
	st_sersock.sin_port = htons(IP_PORT);

	if(bind(i_listenfd,(struct sockaddr*)&st_sersock, sizeof(st_sersock)) < 0) //将套接字绑定IP和端口用于监听
	{
		printf("bind Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	if(listen(i_listenfd, 20) < 0)	//设定可同时排队的客户端最大连接个数
	{
		printf("listen Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	if((epfd = epoll_create(MAXSIZE)) < 0)	//创建epoll实例
	{
		printf("epoll_create Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(-1);
	}
	
	ev.events = EPOLLIN;
	ev.data.fd = i_listenfd;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, i_listenfd, &ev) < 0) 
	{
		printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(-1);
	}
	printf("======waiting for client's request======\n");
	//准备接受客户端连接
	while(1)
	{
		if((nCounts = epoll_wait(epfd, events, MAXSIZE, -1)) < 0) //将收到的事件放到就绪队列中
		{
			printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
			exit(-1);
		}
		else if(nCounts == 0) //获取不到就绪列表
		{
			printf("time out, No data!\n");
		}
		else
		{
			for(int i = 0; i < nCounts; i++) //处理接收到的事件
			{
				int tmp_epoll_recv_fd = events[i].data.fd;
				if(tmp_epoll_recv_fd == i_listenfd)	//有客户端连接请求
				{
					if((i_connfd = accept(i_listenfd, (struct sockaddr*)NULL, NULL)) < 0)	//阻塞等待客户端连接
					{
						printf("accept Error: %s (errno: %d)\n", strerror(errno), errno);
					//	continue;
					}	
					else
					{
						printf("Client[%d], welcome!\n", i_connfd); //新用户添加
					}
	
					ev.events = EPOLLIN;
					ev.data.fd = i_connfd;
					if(epoll_ctl(epfd, EPOLL_CTL_ADD, i_connfd, &ev) < 0)//新用户注册
					{
						printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
						exit(-1);
					}
				}
				else	//若是已连接的客户端发来数据请求
				{
					//接受客户端发来的消息并作处理(小写转大写)后回写给客户端
					memset(msg, 0 ,sizeof(msg));
					if((nrecvSize = read(tmp_epoll_recv_fd, msg, MAXSIZE)) < 0)
					{
						printf("read Error: %s (errno: %d)\n", strerror(errno), errno);
						continue;
					}
					else if( nrecvSize == 0)	//read返回0代表对方已close断开连接。
					{
						printf("client has disconnected!\n");
						epoll_ctl(epfd, EPOLL_CTL_DEL, tmp_epoll_recv_fd, NULL);
						close(tmp_epoll_recv_fd);  //
					
						continue;
					}
					else
					{
						printf("recvMsg:%s", msg);
						for(int i=0; msg[i] != '\0'; i++)
						{
							msg[i] = toupper(msg[i]);
						}
						if(write(tmp_epoll_recv_fd, msg, strlen(msg)+1) < 0)
						{
							printf("write Error: %s (errno: %d)\n", strerror(errno), errno);
						}

					}
				}
			}
		}
	}//while
	close(i_listenfd);
	close(epfd);
	return 0;
}

