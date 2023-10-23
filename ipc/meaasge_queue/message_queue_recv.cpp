#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include<thread>

int main(){
    //创建消息队列
    boost::interprocess::message_queue mq(boost::interprocess::open_only,"MESSAGE_QUEUE");
    unsigned int priority=0;
    boost::interprocess::message_queue::size_type recved_size=0;
    std::string *buffer=new std::string();
    char data[100];
    while(1){
        std::cout<<"test1"<<std::endl;
        mq.receive(data,100,recved_size,priority);
        std::cout<<"buffer_data="<<recved_size<<std::endl;
        std::string str(data);
        std::cout<<str<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    delete buffer;
    return 0;
}
