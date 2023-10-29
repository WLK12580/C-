all:main client
main:epoll_main.o 
	g++ -o main epoll_main.o 

epoll_main.o:epoll_main.cpp
	g++ -c epoll_main.cpp

client:epoll_client.o
	g++ -o client epoll_client.o
epoll_client.o:epoll_client.cpp
	g++ -c epoll_client.cpp

