#include <mpi.h>

#include <iostream>
#include <thread>
int main(int argc,char*argv[]){
    int mype;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&mype); //获取当前进程的进程标识。
    double t1,t2;
    t1=MPI_Wtime(); //获取当前时间
    std::this_thread::sleep_for(std::chrono::seconds(10));
    t2=MPI_Wtime();

    if(mype==0){
        //第一个处理器
        printf("Elapsed time:%f\n",t2-t1);
    }
    MPI_Finalize();

    return 0;
}