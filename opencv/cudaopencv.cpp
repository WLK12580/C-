#include<opencv2/opencv.hpp>
#include<opencv2/core/cuda.hpp>

int main(){
    if(cv::cuda::getCudaEnabledDeviceCount()){
        std::cout<<"检查到的cuda设备的数量="<<cv::cuda::getCudaEnabledDeviceCount()<<std::endl;
    }else{
        std::cout<<"未检测到支持的Cuda设备"<<std::endl;
    }
    return 0;
}

