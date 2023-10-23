#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include<thread>
#include<string.h>

int main(){
    //创建消息队列
    boost::interprocess::message_queue::remove("MESSAGE_QUEUE");
    boost::interprocess::message_queue mq(boost::interprocess::open_or_create,"MESSAGE_QUEUE",1024,100);
    
    std::string str="hello";
    std::string *buffer=&str;
    char buff[100];
    for(int i=0;i<5;i++){
        strcpy(buff,"hello");
        mq.send(buff,100,0); //这里的100要与 boost::interprocess::message_queue mq(boost::interprocess::open_or_create,"MESSAGE_QUEUE",1024,100) 里的100一致，否则运行错误
        std::cout<<"buffer="<<buff<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
