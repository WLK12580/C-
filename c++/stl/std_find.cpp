#include<iostream>
#include<vector>
#include<algorithm>
int main(){
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,0};
    int val=9;
    auto iter=std::find(vec.begin(),std::end(vec),val);
    if(iter!=std::end(vec)){
        std::cout<<"find_value="<<*iter<<std::endl;
    }
    return 0;
}