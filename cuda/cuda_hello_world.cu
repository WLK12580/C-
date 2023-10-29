#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<stdio.h>
__global__ void helloGPU(){
    printf(" hello GPU\n");
}
int main(){
    // cudaError_t cudastatus;
    printf("hello cpu\n");
    helloGPU<<<1,10>>>();
    cudaDeviceReset();
    return 0;
}