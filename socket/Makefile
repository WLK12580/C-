all:sendfile client
sendfile:sendfile.o 
	g++ -o sendfile sendfile.o 

sendfile.o:sendfile_service.cpp
	g++ -c sendfile_service.cpp

client:epoll_client.o
	g++ -o client epoll_client.o
epoll_client.o:sendfile_client.cpp
	g++ -c sendfile_client.cpp
