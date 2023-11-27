#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<iostream>
#include<array>
#include<stdio.h>
__global__ void kernel_func(int *arr3,const int *arr1,const int *arr2){
    printf(" hello GPU\n");
    const unsigned int thread_idx=threadIdx.x;
    arr3[thread_idx]=arr1[thread_idx]*arr2[thread_idx];
    printf("arr1=%d",arr1[thread_idx]);
}
int main(){
    int *arr1[101];
    int *arr2[101];
    int *arr3[101];
    int *arr12[101];
    int *arr11[101];
    int *arr13[101];
    std::cout<<"test01"<<std::endl;
    for(int i=0;i<101;i++){
        std::cout<<"i="<<i<<std::endl;
    }
    std::cout<<"test02"<<std::endl;
    cudaMalloc((void**)&arr3,sizeof(int)*101);
    cudaMalloc((void**)&arr1,sizeof(int)*101);
    cudaMalloc((void**)&arr2,sizeof(int)*101);
    
    cudaMemcpy(arr1,arr11,101*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(arr2,arr12,101*sizeof(int),cudaMemcpyHostToDevice);
    kernel_func<<<1,100>>>(*arr3,*arr1,*arr2);
    cudaMemcpy(arr13,arr3,101*sizeof(int),cudaMemcpyDeviceToHost);

    cudaFree(arr1);
    cudaFree(arr2);
    cudaFree(arr3);
    cudaDeviceReset();
    for(int i=0;i<sizeof(arr13)/sizeof(int);i++){
        std::cout<<" arr["<<i<<"]="<<arr13[i];
    }
    std::cout<<std::endl;

    return 0;
}

