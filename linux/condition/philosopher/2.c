#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define N 5
pthread_mutex_t chop[5];
pthread_mutex_t lock;


void *philosopher(void *arg){
    int i=*(int *)arg;
    int left=i;
    int right=(i+N-1)%N;
while(1){
    sleep(1);
    printf("%d philosopher is thinking\n",i);
    printf("%d is hungry\n",i);
    pthread_mutex_lock(&lock);//?锁住所有的临界区域
    pthread_mutex_lock(&chop[left]);
    printf("%d fetch %d chop\n",i,left);
    pthread_mutex_lock(&chop[right]);
    printf("%d fetch %d chop\n",i,right);
    //eat()
    sleep(1);
    printf("%d is eating\n",i);
    pthread_mutex_unlock(&chop[right]);
    printf("%d release %d chop\n",i,right);
    pthread_mutex_unlock(&chop[left]);
    printf("%d release %d chop\n",i,left);
    pthread_mutex_unlock(&lock);
    }
}

int main(){
    pthread_t pid[5];
    int i;
    pthread_mutex_init(&lock,NULL);
    for(i=0;i<N;i++){
        pthread_mutex_init(&chop[i],NULL);
        pthread_create(&pid[i],NULL,philosopher,(void*)&i);
    }


    for(i=0;i<N;i++){
        pthread_join(pid[i],NULL);
    }

    return 0;

}