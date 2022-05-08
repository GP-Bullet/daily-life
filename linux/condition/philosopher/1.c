//问题产生的原因
//互斥：邻座的哲学家不能同时使用他们之间的叉子
//持有等待：哲学家等待邻座的哲学家用完叉子时不会放下手上已经拿着的叉子
//不可剥夺：哲学家不能从邻座的哲学家手里抢叉子
//环路等待：每位哲学家们左手都持有叉子时，所有人都无法就餐，因为每个人都在等待他们右边的放下左手的叉子

//破坏持有等待，要么不拿要么一下拿两个叉子，不会出现手上拿着一把叉子等待另一把的情况



//破坏环路等待，—— 持有等待的对象不会构成环路
//奇数编号哲学家先拿左筷子，再拿右筷子
//偶数编号哲学家先拿右筷子，再拿左筷子


//轮到哪个线程有顺序吗


//建立相邻哲学家之间的联系，使他们各自成为对方生产者或消费者：

//只有当与之相邻的哲学家完成就餐，哲学家才会取用他们之间的叉子
//破坏的条件：互斥 —— 将邻座哲学家对叉子的竞争关系转换成了协作关系

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
    

#define N 5

pthread_mutex_t chop[N];


void* philosopher(void *arg){
    int i=*(int*)arg;//这样搞   
    int left =i;//i哲学家左手筷子的编号
    int right=(i+N-1)%N;


//?哪里来的5
    while(1){
        printf("%d philosopher is thinking\n",i);
        sleep(1);

        printf("philosopher %d is hungry\n",i);
        if(i%2==0){//偶数先右后左
            pthread_mutex_lock(&chop[right]);
            printf("philosopher %d fetches chopstick %d\n",i,right);
            pthread_mutex_lock(&chop[left]);
            printf("philosopher %d fetches chopstick %d\n",i,left);
            //eat();
            printf("philosopher %d is eating\n",i);
            sleep(1);
            pthread_mutex_unlock(&chop[left]);//?先后有讲究吗
            printf("philosopher %d fetches chopstick %d\n",i,left);
                    
            pthread_mutex_unlock(&chop[right]);
            printf("philosopher %d fetches chopstick %d\n",i,right);
        }else{//奇数先左后右
            pthread_mutex_lock(&chop[left]);
            printf("philosopher %d fetches chopstick %d\n",i,left);
            pthread_mutex_lock(&chop[right]);//?如何确保锁还没有锁过
            printf("philosopher %d fetches chopstick %d\n",i,right);
            //eat();
            printf("philosopher %d is eating\n",i);
            sleep(1);
            pthread_mutex_unlock(&chop[right]);
            printf("philosopher %d fetches chopstick %d\n",i,right);
            pthread_mutex_unlock(&chop[left]);
            printf("philosopher %d fetches chopstick %d\n",i,left);
    
        }
    }
}


int main(){
    pthread_t pid[5];
    int i;
    for(i=0;i<5;i++){
        pthread_mutex_init(&chop[i],NULL);
        pthread_create(&pid[i],NULL,philosopher,(void*)&i);
    }

    for(int i=0;i<5;i++){
        pthread_join(pid[i],NULL);
    }

    return 0;
}