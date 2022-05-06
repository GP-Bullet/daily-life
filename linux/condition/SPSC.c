#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
//因为是有限缓冲问题，有可能会被放满，所以不能用链式队列
//故才用循环队列


//开辟空间？
//传两个参数
//结构体怎么定义
//队列
//void*?

//锁和信号量
//什么时候用到锁
//锁是怎么实现的
//C++学习路线
//什么时候转到C++上 
//写算法题的时候能方便一点但是还不会  泛型编程
#define MAXSIZE 8

pthread_cond_t full;
pthread_cond_t empty;
pthread_mutex_t lock;
//强锁


struct SPSCQueue{
    /* Define Your Data Here */
    int *q;
    int num;
}typedef SPSCQueue;


SPSCQueue *SPSCQueueInit(int capacity);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueuePush(SPSCQueue *pool, void *s);
void SPSCQueueDestory(SPSCQueue *pool);

SPSCQueue *SPSCQueueInit(int capacity)
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
            printf("queue full,consume data,product stop!");
            pthread_cond_wait(&full,&lock);//生产者等待
        }
        //队列不满
        //生产者插入数据
        pool->q[(pool->num)]=rand()%1000;
        printf("produce data %d\n",pool->q[pool->num]);
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
            printf("queue empty,product data,consume stop!");
            pthread_cond_wait(&empty,&lock);
        }
        //队列不为空
        //消费
        (pool->num)--;
        printf("consume data %d\n",pool->q[pool->num]);
        pthread_cond_signal(&full);//通知生产者
        pthread_mutex_unlock(&lock);
    }
    
                                    

}
void* consumer(void* arg){
    
}
void* produceter(void* arg){

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
    int n;
    int ret;
    pthread_t pid,cid;
    
    pool=SPSCQueueInit(n);

    ret=pthread_create(&pid,NULL,(void*)SPSCQueuePush,pool);
    if(ret!=0){
        printf("pthread_create push\n");
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