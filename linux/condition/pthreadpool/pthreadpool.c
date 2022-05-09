/*任务队列
生产者消费者

makefile
动态库和静态库？
*/
#include"pthreadpool.h"


typedef struct Task
{
    void (*function)(void* arg);//保存地址
    void* arg;//保存实参地址
}Task;

const int NUMBER=2;

//线程池结构体
struct ThreadPool
{
    //任务队列
    Task* taskQ;
    int queueCapacity;  //容量
    int queueSize;      //当前任务个数
    int queueFront;    //队头取数据
    int queueRear;      //队尾放数据

    pthread_t managerID;  //管理者线程ID
    pthread_t *threadIDs;  //工作的线程ID
    int minNum;             //最小线程数量
    int maxNum;             //最大线程数量
    int busyNum;            //忙
    int liveNum;            //存活的
    int exitNum;            //销毁
    pthread_mutex_t mutexPool;  //锁整个线程池
    //busyNum 发生变化大
    pthread_mutex_t mutexBusy;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;

    int shutdown;   //是不是要销毁销毁线程池
    
};

ThreadPool*  ThreadPoolCreate(int min,int max,int queueSize)
{   ThreadPool*pool=(ThreadPool*)malloc(sizeof(ThreadPool));
    do{
        
        if(pool==NULL){
            printf("malloc pthreadpool fail...\n");
            break;
        }
        pool->threadIDs=(pthread_t *)malloc(sizeof(pthread_t)*max);
        if(pool->threadIDs==NULL){
            printf("malloc threadIDs fail...\n");
            break;
        }
        memset(pool->threadIDs,0,sizeof(pthread_t)*max);
        pool->minNum=min;
        pool->maxNum=max;
        pool->busyNum=0;
        pool->liveNum=min;  //和最小个数相等
        pool->exitNum=0;

        if( pthread_mutex_init(&pool->mutexPool,NULL)!=0||
            pthread_mutex_init(&pool->mutexBusy,NULL)!=0||
            pthread_cond_init(&pool->notEmpty,NULL)!=0||
            pthread_cond_init(&pool->notFull,NULL)!=0)
            {
                printf("mutex or condition init fail..\n");
                break;
            }
        //任务队列
        pool->taskQ=(Task*)malloc(sizeof(Task)*pool->queueSize);//!
        pool->queueCapacity=queueSize;      //!
        pool->queueSize=0;
        pool->queueFront=0;
        pool->queueRear=0;


        pool->shutdown=0;
        int ret;
        //创建线程
        ret=pthread_create(&pool->managerID,NULL,manager,pool);
        if(ret!=0){
            printf("manager create fail\n");
        }
        for(int i=0;i<min;++i){
            ret=pthread_create(&pool->threadIDs[i],NULL,worker,pool); 
            if(ret!=0){
                printf("worker create fail\n");
            }
        }
        return pool;
    }while(0);

    //释放资源
    if(pool&&pool->threadIDs)free(pool->threadIDs);
    if(pool&&pool->taskQ)free(pool->taskQ);
    if(pool)free(pool);


    return NULL;
}

void threadPoolAdd(ThreadPool* pool,void (*func)(void*),void*arg)
{
    pthread_mutex_lock(&pool->mutexPool);
    while(pool->queueSize==pool->queueCapacity&&!pool->shutdown){
        //满了,生产者阻塞
        printf("hfjdshk\n");
        pthread_cond_wait(&pool->notFull,&pool->mutexPool);
        printf("hfjdskhakjf\n");
    }
    if(pool->shutdown){
        pthread_mutex_unlock(&pool->mutexPool);
        return ;
    }
    //添加任务
    printf("pool->queueRear = %d\n", *(int*)arg);
    pool->taskQ[pool->queueRear].function=func;         //添加到队尾 函数指针保存
    pool->taskQ[pool->queueRear].arg=arg;
    //queueRear向后移动 
    pool->queueRear=(pool->queueRear+1)%pool->queueCapacity;

    pool->queueSize++;//任务+1

    //唤醒阻塞的工作线程（消费者）
    pthread_cond_signal(&pool->notEmpty);

    pthread_mutex_unlock(&pool->mutexPool);
}
int threadPoolDestory(ThreadPool*pool){
    if(pool==NULL){
        return -1;
    }
    //关闭线程池
    pool->shutdown=1;

    //阻塞回收管理者线程
    pthread_join(pool->managerID,NULL);
    //唤醒阻塞的消费者线程 &&被关闭自动退出
    for(int i=0;i<pool->liveNum;i++){
        pthread_cond_signal(&pool->notEmpty);
    }
    //释放堆内存
    //任务队列
    if(pool->taskQ){
        free(pool->taskQ);
    }
    if(pool->threadIDs){
        free(pool->threadIDs);
    }
    
    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool=NULL;

    return 0;
}


//?读写锁
int threadPoolBusyNum(ThreadPool*pool)
{
    pthread_mutex_lock(&pool->mutexBusy);
    int busyNum=pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNum;

}

int threadPoolAliveNum(ThreadPool*pool)
{
    pthread_mutex_lock(&pool->mutexPool);
    int liveNum=pool->liveNum;
    pthread_mutex_unlock(&pool->mutexPool);
    return liveNum;

}

void* worker(void* arg)
{
    ThreadPool* pool=(ThreadPool*)arg;

    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        //是否为空
        while(pool->queueSize==0&& !pool->shutdown){
            pthread_cond_wait(&pool->notEmpty,&pool->mutexPool);//阻塞

            //判断是否要主动退出
            if(pool->exitNum>0){
                pool->exitNum--;
                if(pool->liveNum>pool->minNum){
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);//拿到锁之后解开
                    threadExit(pool);
                }
                
            }

        }
        //判断是否被关闭
        if(pool->shutdown){
            pthread_mutex_unlock(&pool->mutexPool);
            threadExit(pool);
        }
        //从任务队列里取出一个任务
        Task task;
        task.function =pool->taskQ[pool->queueFront].function;
        task.arg=pool->taskQ[pool->queueFront].arg;

        //移动头结点
        pool->queueFront=(pool->queueFront+1)%pool->queueCapacity;
        pool->queueSize--;

        //解锁
        //唤醒生产者        
        pthread_cond_signal(&pool->notFull);
        pthread_mutex_unlock(&pool->mutexPool);
        
        printf("thread %lu start working...\n",pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;//忙线程+1
        pthread_mutex_unlock(&pool->mutexBusy);
        printf("task.arg = %p \n", task.arg);
        //调用函数
        task.function(task.arg);//?
        printf("task.arg = %p \n", task.arg);
       // free(task.arg);                       //*任务函数传的参数是堆内存
        //!这里free的是num
        task.arg=NULL;


        printf("thread %ld end working...\n",pthread_self());//做完之后 忙线程-1
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
}

void* manager(void* arg)
{
    ThreadPool* pool=(ThreadPool*)arg;
    while(!pool->shutdown){
        //3秒检测一次
        sleep(3);
        //取数据
        //加锁 在读这些数据时 可能别的线程在写这些数据
        
        //保护了整个线程池
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize=pool->queueSize;
        int liveNum=pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        //忙的线程数量

        //提高操作效率
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum=pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);
        
        //添加线程

        //?方案

        //任务个数>存活线程数&&存活线程数<最大线程数
        if(queueSize>liveNum && liveNum < pool->maxNum){
            int counter=0;
            pthread_mutex_lock(&pool->mutexPool);
            for(int i=0;i<pool->maxNum && counter<NUMBER
                && pool->liveNum<pool->maxNum;++i)
            {      //找空闲ID
                if(pool->threadIDs[i]==0){
                    pthread_create(&pool->threadIDs[i],NULL,worker,pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }

        //销毁线程
        //忙的线程*2<存活线程数 && 存活线程 >最小线程数
        if(busyNum*2<liveNum && liveNum>pool->minNum){
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum=NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            //工作的线程自杀  阻塞的线程主动退出
            for(int i=0;i<NUMBER;i++){
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return NULL; 
}

void threadExit(ThreadPool* pool)
{
    pthread_t tid=pthread_self();
    for(int i=0;i<pool->maxNum;i++){
        if(pool->threadIDs[i]==tid){
            pool->threadIDs[i]=0;
            printf("thread %ld exit...\n",tid);
            break;
        }
    }
    pthread_exit(NULL);
}

void taskFuction(void *arg)
{   
    int num=*(int *)arg;
    printf("thread %lu is working, number=%d\n",pthread_self(),num);
    sleep(1);
}

int main()
{
    //创建线程池
    ThreadPool* pool=ThreadPoolCreate(3,10,100);//最小线程数
    
    int *num=(int *)malloc(sizeof(int) * 100);
    for(int i=0;i<100;i++){
        num[i]=i;
        threadPoolAdd(pool,taskFuction,(void*)&num[i]);
    }
    
    //free(num);
    
    sleep(30);//?
    
    threadPoolDestory(pool);
    //free(num);
    return 0;
}