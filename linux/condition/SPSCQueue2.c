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


SPSCQueue *SPSCQueueInit();
void SPSCQueuePush(SPSCQueue *pool, void *s);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueueDestory(SPSCQueue *);

SPSCQueue *SPSCQueueInit()
{
    SPSCQueue *Q;
    Q->front=0;
    Q->rear=0;

    return Q;
}

void SPSCQueuePush(SPSCQueue *pool, void *s)
{
    for(;;){

        pool=malloc(sizeof(SPSCQueue));
        
        pthread_mutex_lock(&lock);
        pool->data[pool->rear]=(int) *s;
        pool->rear=(pool->rear+1)%MAXSIZE;
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&has_product);//将等待在该条件变量上的一个线程唤醒
        sleep(rand()%5);
    
    }


    if((pool->rear+1)%MAXSIZE==pool->front){//队列满
        ;
    }
    
    
}

void *SPSCQueuePop(SPSCQueue *pool)
{   
    for(;;){
        pthread_mutex_lock(&lock);
        while(pool->front==pool->rear){//队列是空的
            pthread_cond_wait(&has_product,&lock);
        }
    }
    //消费一个数据
    pool->front=(pool->front+1)%MAXSIZE;
    pthread_mutex_unlock(&lock);
    printf("-Consume %lu ---%d\n",pthread_self(),pool->data);
    free(pool);
    sleep(rand()%5);        //?

}







int main(){
    struct Param{
        SPSCQueue *pool;
        void *s;
    }
    Param q;
    
    int ret;
    pthread_t pid,cid;
    SPSCQueueInit();

    ret=pthread_create(&pid,NULL,SPSCQueuePush,&);
    if(ret!=0);;
    
    ret=pthread_create(&cid,NULL,SPSCQueuePop,&);
    if(ret!=0);;

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    return 0;
}