#include"pthreadpool.h"
#include<stdio.h>

void taskFuction(void *arg)
{   
    int num=*(int *)arg;
    printf("thread %lu is working,number=%d\n",pthread_self(),num);
    usleep(1000);
}

int main()
{
    //创建线程池
    ThreadPool* pool=ThreadPoolCreate(3,10,100);//最小线程数
    for(int i=0;i<100;i++){
        int *num=(int *)malloc(sizeof(int));
        *num=i+100;
        threadPoolAdd(pool,taskFuction,num);
    }

    sleep(30);//?

    threadPoolDestory(pool);
    return 0;
}