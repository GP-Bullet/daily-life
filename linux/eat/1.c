//问题产生的原因
//互斥：邻座的哲学家不能同时使用他们之间的叉子
//持有等待：哲学家等待邻座的哲学家用完叉子时不会放下手上已经拿着的叉子
//不可剥夺：哲学家不能从邻座的哲学家手里抢叉子
//环路等待：每位哲学家们左手都持有叉子时，所有人都无法就餐，因为每个人都在等待他们右边的放下左手的叉子

//破坏持有等待，要么不拿要么一下拿两个叉子，不会出现手上拿着一把叉子等待另一把的情况

//破坏环路等待，—— 持有等待的对象不会构成环路
//奇数编号哲学家先拿左筷子，再拿右筷子
//偶数编号哲学家先拿右筷子，再拿左筷子

#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
    

#define N 5
sem_t chop[5];
pthread_mutex_t lock;

void* philosopher(void *arg){
    int i=(int)arg;
}


int main(){
    pthread_t pid[5];
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<5;i++){
        sem_init(&chop[i],0,1);
        pthread
    }
}