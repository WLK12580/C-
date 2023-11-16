#include<iostream>
#include<thread>
typedef struct Person{
    std::string name;
    long long age=0;
    long long heigh=0;
} person;
void WriteThread(Person &per,int i){
    while(1){
        per.name="xiaoming";
        per.age=i;
        per.heigh=i+1000;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        i++;
        // std::cout<<"Write--------name="<<per.name<<" age="<<per.age<<" heigh="<<per.heigh<<std::endl;
    }
}
void ReadThread(const Person &per){
    while(1){
        std::cout<<"name="<<per.name<<" age="<<per.age<<" heigh="<<per.heigh<<std::endl;
        if(per.heigh-per.age!=1000){
            std::cout<<"读异常："<<" heigh="<<per.heigh<<" age="<<per.age<<std::endl;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
int main(){
    person person;
    int i=0;
    std::thread th1(WriteThread,std::ref(person),i);

    std::thread th2(ReadThread,std::ref(person));


    th1.join();
    th2.join();


    return 0;

    
}
/* 一线程写数据，一线程读数据：不加锁的情况下，出现脏数据
name=xiaoming age=57047 heigh=58047
name=xiaoming age=57048 heigh=58048
name=xiaoming age=57049 heigh=58049
name=xiaoming age=57050 heigh=58050  //重复读，读线程读取中，写线程没来得及更新数据
name=xiaoming age=57050 heigh=58050
name=xiaoming age=57051 heigh=58051


name=xiaoming age=27763 heigh=28763
name=xiaoming age=27764 heigh=28764 //读取丢失，即写线程写完之后 读线程没来得及读取，写线程再次执行写操作
name=xiaoming age=27766 heigh=28766
name=xiaoming age=27767 heigh=28767

*/