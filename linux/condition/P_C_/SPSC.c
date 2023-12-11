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
    int *q;//?                  
    int num;
}typedef SPSCQueue;


SPSCQueue *SPSCQueueInit(int capacity);
void *SPSCQueuePop(SPSCQueue *queue);
void SPSCQueuePush(SPSCQueue *queue, void *s);
void SPSCQueueDestory(SPSCQueue *queue);

SPSCQueue *SPSCQueueInit(int capacity)
{   
    pthread_mutex_init(&lock,NULL); 
    pthread_cond_init(&full,NULL);
    pthread_cond_init(&empty,NULL);

    SPSCQueue * queue=(SPSCQueue *)malloc(sizeof(SPSCQueue));//?
    (queue->q)=(int *)malloc(sizeof(int));//?
    queue->num=0;
    memset(queue->q,0,sizeof(queue->q));
    return queue;
    
}


void SPSCQueuePush(SPSCQueue *queue, void *s)
{   
    
    srand((unsigned long)time(NULL));
    
    for(;;){
        
        
        pthread_mutex_lock(&lock);
        while(queue->num>=MAXSIZE){//队列满
            pthread_cond_signal(&empty);
            printf("queue full,consume data,product stop!");
            pthread_cond_wait(&full,&lock);//生产者等待
        }
        //队列不满
        //生产者插入数据
        queue->q[(queue->num)]=rand()%1000;
        printf("produce data %d\n",queue->q[queue->num]);
        (queue->num)++;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);
        
        //sleep(rand()%5);
    
    }
    
}

void *SPSCQueuePop(SPSCQueue *queue)
{   
    
    
    for(;;){
        pthread_mutex_lock(&lock);
        while(queue->num==0){//队列是空的
            pthread_cond_signal(&full);
            printf("queue empty,product data,consume stop!");
            pthread_cond_wait(&empty,&lock);
        }
        //队列不为空
        //消费
        (queue->num)--;
        printf("consume data %d\n",queue->q[queue->num]);
        pthread_cond_signal(&full);//通知生产者
        pthread_mutex_unlock(&lock);
    }
    
                                    

}


void SPSCQueueDestory(SPSCQueue *queue)
{
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    free(queue->q);
    free(queue);
    
}




int main(){
    SPSCQueue *queue;
    int n;
    printf("The capacity is\n");
    scanf("%d",&n);
    int ret;
    pthread_t pid,cid;
    
    queue=SPSCQueueInit(n);

    ret=pthread_create(&pid,NULL,(void*)SPSCQueuePush,queue);
    if(ret!=0){
        printf("pthread_create producter\n");
    }
    
    ret=pthread_create(&cid,NULL,(void*)SPSCQueuePop,queue);
    if(ret!=0);{
        printf("pthread_create consumer\n");
    }

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);



    SPSCQueueDestory(queue);

    return 0;
}