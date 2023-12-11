#include"Ser_ppool.h"
#include"Ser_ppool.cpp"
#include<unistd.h>
#include<stdio.h>
#include<jsoncpp/json/json.h>


void taskFuction(void *arg)
{   
    int num=*(int *)arg;
    printf("thread %lu is working, number=%d\n",pthread_self(),num);
    sleep(1);
}

int main()
{
    ThreadPool<int> pool(3,10);
    for(int i=0;i<100;i++)
    {
         int * num=new int(i+100);
        pool.addTask(Task<int>(taskFuction,num));
    }
    sleep(20);

    return 0;
}