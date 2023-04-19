//pv操作：生产者与消费者经典问题
//author:leaf
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 32             /*缓冲数目*/

#define P(x)     sem_wait(&x)
#define V(x)    sem_post(&x)

int in = 0;         /*生产者放置产品的位置*/
int out = 0;             /*消费者取产品的位置*/

int buff[M] = {0};     /*缓冲初始化为0， 开始时没有产品*/

sem_t empty_sem;         /*同步信号量，当满了时阻止生产者放产品*/
sem_t full_sem;         /*同步信号量，当没产品时阻止消费者消费*/
pthread_mutex_t mutex; /*互斥信号量， 一次只有一个线程访问缓冲*/

/*
 *output the buffer
 */
void print()
{
    int i;
    for(i = 0; i < M; i++)
        printf("%d ", buff[i]);
    printf("\n");
}

/*
 *producer
 */
void *producer()
{
    for(;;)
    {
        sleep(1);

        P(empty_sem);
        pthread_mutex_lock(&mutex);

        in = in % M;
        printf("(+)produce a product. buffer:");

        buff[in] = 1;
        print();
        ++in;

        pthread_mutex_unlock(&mutex);
        V(full_sem);
    }
}

/*
 *consumer
 */
void *consumer()
{
    for(;;)
    {
        sleep(2);

        P(full_sem);
        pthread_mutex_lock(&mutex);

        out = out % M;
        printf("(-)consume a product. buffer:");

        buff[out] = 0;
        print();
        ++out;

        pthread_mutex_unlock(&mutex);
        V(empty_sem);
    }
}

void sem_mutex_init()
{
    /*
     *semaphore initialize
     */
    int init1 = sem_init(&empty_sem, 0, M);
    int init2 = sem_init(&full_sem, 0, 0);
    if( (init1 != 0) && (init2 != 0))
    {
        printf("sem init failed \n");
        exit(1);
    }
    /*
     *mutex initialize
     */
    int init3 = pthread_mutex_init(&mutex, NULL);
    if(init3 != 0)
    {
        printf("mutex init failed \n");
        exit(1);
    }
    
}
int main()
{
    pthread_t id1;
    pthread_t id2;
    int i;
    int ret;

    sem_mutex_init();
    
    /*create the producer thread*/
    ret = pthread_create(&id1, NULL, producer, NULL);
    if(ret != 0)
    {
        printf("producer creation failed \n");
        exit(1);
    }
    
    /*create the consumer thread*/
    ret = pthread_create(&id2, NULL, consumer, NULL);
    if(ret != 0)
    {
        printf("consumer creation failed \n");
        exit(1);
    }

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    exit(0);
}