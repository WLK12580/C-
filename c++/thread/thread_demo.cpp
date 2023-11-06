#include<iostream>
#include<thread>

void Thread(int time){
    std::cout<<"sub thread begin"<<std::endl;
    std::cout<<"sub thread id:"<<std::this_thread::get_id()<<std::endl;
    std::this_thread::yield();
    for(int i=0;i<time;i++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<<"sub thread run time:"<<i<<std::endl;
    }
    std::cout<<"sub thread end"<<std::endl;
}
int main(){
    std::cout<<"main thread begin"<<std::endl;
    std::cout<<"mian thread id: "<<std::this_thread::get_id()<<std::endl;
    int data=20;
    std::thread th1(Thread,std::ref(data));
    th1.join();//阻塞主线程等待子线程结束

    return 0;

}