#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//!错了
struct SPSCQueue{
    struct msg *next;
    int data;
}typedef SPSCQueue;

typedef struct Queue
{
    SPSCQueue* front;       /*队头指针*/
    SPSCQueue* back;        /*队尾指针*/
}Queue;

pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;


SPSCQueue *SPSCQueueInit(int threadNumber);
void SPSCQueuePush(SPSCQueue *pool, void *s);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueueDestory(SPSCQueue *);

SPSCQueue *SPSCQueueInit(int threadNumber){
    
    Queue *mp;
    //申请头结点内存空间
	QueueNode *s = (QueueNode *)malloc(sizeof(QueueNode));
	assert(s != NULL);
	//初始化时，将头指针和尾指针都指向头结点
	Q->front = Q->tail = s;
	//将头结点的下一结点赋空
	Q->tail->next = NULL;


    pthread_create(&threadNumber,NULL,,NULL);
    pthread_join(threadNumber,NULL);
}

void SPSCQueuePush(SPSCQueue *pool, void *s){

}
void *SPSCQueuePop(SPSCQueue *pool){
    
}

int main(){
    pthread_t pid,cid;
    SPSCQueueInit(pid);
    SPSCQueueInit(cid);


}