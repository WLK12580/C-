// demo.cpp
#include<torch/torch.h>
#include<iostream>
//using namespace std;
int main(){
    torch::Tensor tensor = torch::ones(3);
    std::cout << tensor << std::endl;
}