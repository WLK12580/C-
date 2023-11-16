#include<iostream>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<semaphore.h>

#define SEM "SEM_NAME"
int main(){
    key_t shm=ftok(".",1);


    int shmid=shmget(shm,1024,IPC_CREAT|0666);
    if(shmid<0){
        printf("shmget Error:%s-%d\n",strerror(errno),errno);
        exit(-1);
    }
    sem_t *semid=sem_open(SEM,O_CREAT|O_RDWR,0666,1);
    if(semid==SEM_FAILED){
        printf("sem Error:%s %d\n",strerror(errno),errno);
        exit(-1);
    }
    void *shmaddr=shmat(shmid,NULL,0);
    std::cout<<"test1"<<std::endl;
    if(shmaddr==nullptr){
        printf("Shmat Error:%s %d\n",strerror(errno),errno);
        exit(-1);
    }
    char *readbuf=(char*)shmaddr;
    sem_wait(semid);
    printf("read data:%s",readbuf);
    sem_post(semid);
    sem_close(semid);
    return 0;
}