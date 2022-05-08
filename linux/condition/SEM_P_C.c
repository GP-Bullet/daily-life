#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


int NUM;

sem_t blankNum,productNum;

void *producer(void *arg)
{   
    int *queue=(int *)arg;
    int i=0;
    while(1){
        sem_wait(&blankNum);//生产将blank--，为0则阻塞
        queue[i]=rand()%1000+1;
        printf("produce----%d\n",queue[i]);
        sem_post(&productNum);  //产品++
        
        i=(i+1)%NUM;        
        sleep(rand()%1);
    }    
}


void *consumer(void *arg){
    int *queue=(int *)arg;
    int i=0;
    while(1){

        sem_wait(&productNum);//消费将产品数--，为零时阻塞等待
        printf("consume----%d\n",queue[i]);
        queue[i]=0;
        sem_post(&blankNum);//将blank++

        i=(i+1)%NUM;
        sleep(rand()%3);
    }
}




int main()
{
    
    printf("The capacity is\n");
    scanf("%d",&NUM);

    int queue[NUM];//环形队列

    pthread_t pid,cid;

    sem_init(&blankNum,0,NUM);//初始时blank为NUM   
    sem_init(&productNum,0,0);//初始时产品为0

    pthread_create(&pid,NULL,producer,(void*)queue);
    pthread_create(&cid,NULL,consumer,(void*)queue);

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    sem_destroy(&blankNum);
    sem_destroy(&productNum);

    return 0;
}