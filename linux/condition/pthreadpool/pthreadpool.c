/*任务队列
生产者消费者

makefile
动态库和静态库？
*/

#include"pthreadpool.h"


typedef struct Task
{
    void (*function)(void* arg);
    void* arg;//保存实参地址
}Task;

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
    pthread_t threadIDs;  //工作的线程ID
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

ThreadPool*  ThreadPoolCreate(int min,int max,int queSize)
{
    do{
        ThreadPool*pool=(ThreadPool*)malloc(sizeof(ThreadPool));
        if(pool==NULL){
            printf("malloc pthreadpool fail...\n");
            return NULL;
        }
        pool->threadIDs=(pthread_t *)malloc(sizeof(pthread_t)*max);
        if(pool->threadIDs==NULL){
            printf("malloc threadIDs fail...\n");
            return NULL;
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
            pthread_cond_init(&pool->notFull,NULL)!=0){
                printf("mutex or condition init fail..\n");
                return 0;
            }
        //任务队列
        pool->taskQ=(Task*)malloc(sizeof(Task)*pool->queueSize);
        pool->queueCapacity=pool->queueSize;
        pool->queueSize=0;
        pool->queueFront=0;
        pool->queueRear=0;


        pool->shutdown=0;

        //创建线程
        pthread_create(&pool->managerID,NULL,manager,NULL);
        for(int i=0;i<min;++i){
            pthread_create(&pool->threadIDs[i],NULL,worker,NULL);  
        }
        return pool;
    }while(0);

    //释放资源
    if(pool&&pool->threadIDs)free(pool->threadIDs);
    if(pool&&pool->taskQ)free(pool->taskQ);
    if(pool)free(pool);


    return NULL;
}


void* worker(void* arg)
{
    ThreadPool* pool=(ThreadPool*)arg;

    while(1){
        pthread_mutex_lock(&pool->mutexPool);

        while(pool->queueSize==0&& !pool->shutdown){
            pthread_cond_wait(&pool->notEmpty,)
        }
    }
}



