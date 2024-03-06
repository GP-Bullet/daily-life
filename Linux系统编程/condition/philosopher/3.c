#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
//因为同时只允许有四位哲学家同时拿起左筷子，
//因此我们可以设置一个信号量r，使其初始值为4，
//然后每当一位哲学家企图去拿起他左边的筷子的时候，
//先对信号量做一次P操作，从而当第五位哲学家企图去拿做筷子的时候，
//对r做一次P操作，r = -1，由r < 0得第五位哲学家的线程被阻塞，
//从而不能拿起左筷子，因此也就避免了死锁问题。
//然后当哲学家放下他左边的筷子的时候，就对r做一次V操作。

sem_t  sem;
pthread_mutex_t chop[5];
#define N 5
//?为什么用了信号量还要用互斥量



void* philosopher(void *arg){

    int i=*(int *)arg;
    int left=i;
    int right=(i+N-1)%N;
while(1)
{


    sleep(1);
    printf("%d is thinking\n",i);
    printf("%d is hungry\n",i);
    sem_wait(&sem);//--,0阻塞   同时最多来四个
    //该信号量    ：他来了但他没有拿筷子
    pthread_mutex_lock(&chop[left]);
    printf("%d fetch %d chop\n",i,left);
    pthread_mutex_lock(&chop[right]);
    printf("%d fetch %d chop\n",i,right);
    //eat()
    printf("%d is eating \n",i);
    sleep(1);
    
    pthread_mutex_unlock(&chop[left]);
    printf("%d realese %d (left)chop\n",i,left);
    sem_post(&sem);//放下了左边的筷子，多一个线程来拿左筷子
    printf("sem ++\n");
    pthread_mutex_unlock(&chop[right]);
    printf("%d realese %d (right)chop\n",i,right);
}
}
int main(){
    pthread_t pid[N];
    sem_init(&sem,0,4);
    int i;
    for(i=0;i<N;i++){
        pthread_mutex_init(&chop[i],NULL);
        pthread_create(&pid[i],NULL,philosopher,(void*)&i);
    }

    for(i=0;i<N;i++){
        pthread_join(pid[i],NULL);
    }
    return 0;
}