#include<iostream>
#include<list>
#include<mutex>
#include<thread>
#include<algorithm>
std::mutex mt;
void addValueToList(const int &val,std::list<int>&list){
    // std::lock_guard<std::mutex> lg(mt);
    list.emplace_back(val);
}
void getValueFromList(const int &val,int &ret_val,const std::list<int> &list){
    std::lock_guard<std::mutex> lg(mt);
    ret_val=std::find(list.begin(),list.end(),val)!=list.end()?val:-1;
}

int main(){
    std::list<int>list;
    int retValue=0;
    int searceValue=9;
    std::thread th([&list]() {
      {
        std::lock_guard<std::mutex> lg(mt);
        for (int i = 0; i < 100; i++) {
          addValueToList(i, list);
          std::this_thread::sleep_for(std::chrono::seconds(1));
          std::cout << "value=" << i << std::endl;
        }
      }
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th1([&](){
        getValueFromList(searceValue,retValue,list);
        std::cout<<"retValue="<<retValue<<std::endl;
    });
    
    th1.join();
    th.join();
    return 0;
}