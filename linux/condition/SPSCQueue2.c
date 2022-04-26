#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//因为是有限缓冲问题，有可能会被放满，所以不能用链式队列
//故才用循环队列

#define MAXSIZE 4096


pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;

typedef int QElemType; 

struct SPSCQueue{
    /* Define Your Data Here */
    int front;
    int rear;
    QElemType data[4096];
}typedef SPSCQueue;


SPSCQueue *SPSCQueueInit(int threadNumber);
void SPSCQueuePush(SPSCQueue *pool, void *s);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueueDestory(SPSCQueue *);

SPSCQueue *SPSCQueueInit(int threadNumber){
    SPSCQueue *Q;
    Q->front=0;
    Q->rear=0;

    return Q;
}

void SPSCQueuePush(SPSCQueue *pool, void *s){
    
}

void *SPSCQueuePop(SPSCQueue *pool){

}


int main(){
    pthread_t pid,cid;

}