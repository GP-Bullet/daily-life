#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//因为是有限缓冲问题，有可能会被放满，所以不能用链式队列
//故才用循环队列


//开辟空间？
//传两个参数
//结构体怎么定义
//队列
//void*?
#define MAXSIZE 8

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full=PTHREAD_COND_INITIALIZER;
pthread_cond_t empty=PTHREAD_COND_INITIALIZER;

typedef int QElemType; 

struct SPSCQueue{
    /* Define Your Data Here */
    int front;
    int rear;
    QElemType data[8];
}typedef SPSCQueue;


SPSCQueue *SPSCQueueInit();
void *SPSCQueuePush(void *pool);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueueDestory(SPSCQueue *);

SPSCQueue *SPSCQueueInit()
{
    SPSCQueue *bq;
    bq->front=0;
    bq->rear=0;

    return bq;
}


void *SPSCQueuePush(void *pool)
{   
    SPSCQueue *bq=(SPSCQueue*)pool;
    srand((unsigned long)time(NULL));
    for(;;){
        int data=rand()%1024;
        bq=malloc(sizeof(SPSCQueue));
        
        pthread_mutex_lock(&lock);
        while((bq->rear+1)%MAXSIZE==bq->front){//队列满
            pthread_cond_signal(&empty);
            printf("queue full,consume data,product stop!");
            pthread_cond_wait(&empty,&lock);
        }
        //队列不满
        //生产者插入数据

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);
        
        //sleep(rand()%5);
    
    }
    
}

void *SPSCQueuePop(void* pool)
{   
    SPSCQueue *bq=(SPSCQueue*)pool;
    int data;
    for(;;){
        pthread_mutex_lock(&lock);
        while(bq->front==bq->rear){//队列是空的
            pthread_cond_signal(&full);
            printf("queue empty,product data,consume stop!");
            pthread_cond_wait(&empty,&lock);
        }
        //队列不为空
        //消费

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);
    }
    
                                    

}

void SPSCQueueDestory(SPSCQueue *)






int main(){
    
    
    int ret;
    pthread_t pid,cid;
    SPSCQueue *bq;
    SPSCQueueInit();

    ret=pthread_create(&pid,NULL,SPSCQueuePush,(void*)&bq);
    if(ret!=0);;
    
    ret=pthread_create(&cid,NULL,SPSCQueuePop,(void*)&bq);
    if(ret!=0);;

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    return 0;
}