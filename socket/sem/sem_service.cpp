#include<iostream>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/stat.h>
#include <stdlib.h>
#include<unistd.h>
#include <errno.h>
#include<string.h>
#include <sys/wait.h>
#define SHARPATH "/home/wlk/learn/socket/sem/SHARFILE"

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};
void PV(int semid,int op){
    struct sembuf sem_b;
    sem_b.sem_num=0; //信号量集中信号量的编号
    sem_b.sem_op=op; //信号量的值增加量
    sem_b.sem_flg=SEM_UNDO; //进程退出时取消正在进行的semop操作；
    semop(semid,&sem_b,1);  //第三个参数指定要执行的操作个数
}

int main() {
    int semid=semget(IPC_PRIVATE,1,0666); //第二个参数是信号量集中 信号的个数；
    union semun sem_un;
    sem_un.val=1;
    semctl(semid,0,SETVAL,sem_un); 
    pid_t forkid=fork();
    if(forkid<0){
        return -1;
    }else if(forkid==0){ 
        printf("child try get binary sem\n");
        PV(semid,-1);
        printf("child using sem\n");
        sleep(5);
        PV(semid,1);
        exit(0);
    }else{
        printf("parent try get binary sem\n");
        PV(semid,-1);
        printf("parent using sem\n");
        sleep(5);
        PV(semid,1);
    }
    waitpid(forkid,NULL,0);
    semctl(semid,0,IPC_RMID,sem_un);
  return 0;
}