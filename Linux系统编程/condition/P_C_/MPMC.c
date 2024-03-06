#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
//模型有什么用
//管道

//因为是有限缓冲问题，有可能会被放满，所以不能用链式队列
//故才用循环队列


//开辟空间？
//传两个参数
//结构体怎么定义
//队列
//void*?

//死锁有几种情况：对一个锁反复lock 
//进程和线程和内核                      
//我们用进程去做什么用线程去做什么


#define MAXSIZE 8

pthread_cond_t full;
pthread_cond_t empty;
pthread_mutex_t lock;



struct SPSCQueue{
    /* Define Your Data Here */
    int *q;
    int num;
}typedef SPSCQueue;


SPSCQueue *SPSCQueueInit();
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueuePush(SPSCQueue *pool, void *s);
void SPSCQueueDestory(SPSCQueue *pool);

SPSCQueue *SPSCQueueInit()
{   
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&full,NULL);
    pthread_cond_init(&empty,NULL);

    SPSCQueue * pool=(SPSCQueue *)malloc(sizeof(SPSCQueue));
    (pool->q)=(int *)malloc(sizeof(int)*2);
    pool->num=0;
    memset(pool->q,0,sizeof(pool->q)); 
    return pool;
    
}


void SPSCQueuePush(SPSCQueue *pool, void *s)
{   
    
    srand((unsigned long)time(NULL));
    
    for(;;){
        
        
        pthread_mutex_lock(&lock);
        while(pool->num>=MAXSIZE){//队列满
            pthread_cond_signal(&empty);    
            printf("queue full,consume data,product stop!\n");
            pthread_cond_wait(&full,&lock);//生产者等待
        }
        //队列不满
        //生产者插入数据
        pool->q[(pool->num)]=rand()%1000;
        printf("id %lu produce data %d\n",pthread_self(),pool->q[pool->num]);
        (pool->num)++;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);
        
        //sleep(rand()%5);
    
    }
    
}

void *SPSCQueuePop(SPSCQueue *pool)
{   
    
    
    for(;;){
        pthread_mutex_lock(&lock);
        while(pool->num==0){//队列是空的
            pthread_cond_signal(&full);
            printf("queue empty,product data,consume stop!\n");
            pthread_cond_wait(&empty,&lock);
        }
        //队列不为空
        //消费
        (pool->num)--;
        printf("id %lu consume data %d\n",pthread_self(),pool->q[pool->num]);
        pthread_cond_signal(&full);//通知生产者
        pthread_mutex_unlock(&lock);
    }
    
                                    

}

void SPSCQueueDestory(SPSCQueue *pool)
{
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    free(pool->q);
    free(pool);
    
}

int main(){
    SPSCQueue *pool;
    
    int ret;
    pthread_t pid,cid;
    
    pool=SPSCQueueInit();

    ret=pthread_create(&pid,NULL,(void*)SPSCQueuePush,pool);
    if(ret!=0){
        printf("pthread_create push\n");
    }
    ret=pthread_create(&pid,NULL,(void*)SPSCQueuePush,pool);
    if(ret!=0){
        printf("pthread_create push\n");
    }
    ret=pthread_create(&pid,NULL,(void*)SPSCQueuePush,pool);
    if(ret!=0){
        printf("pthread_create push\n");
    }

    ret=pthread_create(&cid,NULL,(void*)SPSCQueuePop,pool);
    if(ret!=0);{
        printf("pthread_create pop\n");
    }

    ret=pthread_create(&cid,NULL,(void*)SPSCQueuePop,pool);
    if(ret!=0);{
        printf("pthread_create pop\n");
    }
    ret=pthread_create(&cid,NULL,(void*)SPSCQueuePop,pool);
    if(ret!=0);{
        printf("pthread_create pop\n");
    }
    
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);



    SPSCQueueDestory(pool);

    return 0;
}