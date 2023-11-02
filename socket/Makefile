all:sendfile client
sendfile:sendfile.o 
	g++ -o sendfile sendfile.o 

sendfile.o:sendfile.cpp
	g++ -c sendfile.cpp

client:epoll_client.o
	g++ -o client epoll_client.o
epoll_client.o:epoll_client.cpp
	g++ -c epoll_client.cpp
