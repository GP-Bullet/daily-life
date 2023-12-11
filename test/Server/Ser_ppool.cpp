#include"Ser_ppool.h"
#include <cstddef>
#include<iostream>
#include<string.h>
#include<string>
#include<unistd.h>
using namespace std;  

template <typename T> 
ThreadPool<T>::ThreadPool(int min,int max)
{   
    //实例化任务队列
    do{
    taskQ=new TaskQueue<T>;

        threadIDs=new pthread_t[max];
        
        if(threadIDs==nullptr){
            cout<<"malloc threadIDs fail...\n"<<endl;
            break;
        }
        memset(threadIDs,0,sizeof(pthread_t)*max);
        
        minNum=min;
        maxNum=max;
        busyNum=0;
        liveNum=min;  //和最小个数相等
        exitNum=0;


        shutdown=false;
        if( pthread_mutex_init(&mutexPool,NULL)!=0||
            pthread_cond_init(&notEmpty,NULL)!=0)
            {
                cout<<"mutex or condition init fail..\n";
                break;
            }
        int ret;
        //创建线程
        ret=pthread_create(&managerID,NULL,manager,this);
        if(ret!=0){
            cout<<"manager create fail\n";
        }
        for(int i=0;i<min;++i){
            ret=pthread_create(&threadIDs[i],NULL,worker,this); 
            if(ret!=0){
                cout<<"worker create fail\n";
            }
        }
        return ;
    }while(0);

    //释放资源
    if(threadIDs)delete[]threadIDs;
    if(taskQ)delete taskQ;
}



template <typename T> 
void ThreadPool<T>::addTask(Task<T> task)
{
    if(shutdown){
        return ;
    }
    //添加任务
    taskQ->addTask(task);

    //唤醒阻塞的工作线程（消费者）
    pthread_cond_signal(&notEmpty);


}


template <typename T> 
ThreadPool<T>::~ThreadPool()
{

    //关闭线程池
    shutdown=true;

    //阻塞回收管理者线程
    pthread_join(managerID,NULL);
    //唤醒阻塞的消费者线程 &&被关闭自动退出
    for(int i=0;i<liveNum;i++){
        pthread_cond_signal(&notEmpty);
    }
    //释放堆内存
    //任务队列
    if(taskQ){
        delete taskQ;
    }
    if(threadIDs){
        delete []threadIDs;
    }
    
    pthread_mutex_destroy(&mutexPool);
    pthread_cond_destroy(&notEmpty);
}


//?读写锁
template <typename T> 
int ThreadPool<T>::getBusyNum()
{
    pthread_mutex_lock(&mutexPool);
    int busyNum=this->busyNum;
    pthread_mutex_unlock(&mutexPool);
    return busyNum;

}
template <typename T> 
int ThreadPool<T>::getLiveNum()
{
    pthread_mutex_lock(&mutexPool);
    int liveNum=this->liveNum;
    pthread_mutex_unlock(&mutexPool);
    return liveNum;

}

template <typename T> 
void* ThreadPool<T>::worker(void* arg)
{
    ThreadPool* pool=static_cast<ThreadPool*>(arg);

    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        //是否为空
        while(pool->taskQ->taskNumber()==0&& !pool->shutdown){
            pthread_cond_wait(&pool->notEmpty,&pool->mutexPool);//阻塞

            //判断是否要主动退出
            if(pool->exitNum>0){
                pool->exitNum--;
                if(pool->liveNum>pool->minNum){
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);//拿到锁之后解开
                    pool->threadExit();//类的非静态成员函数
                }
                
            }

        }
        //判断是否被关闭
        if(pool->shutdown){
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }
        //从任务队列里取出一个任务
        Task<T> task=pool->taskQ->takeTask();


        //解锁
        //唤醒生产者            
        pool->busyNum++;//忙线程+1
        cout<<"thread "<<to_string(pthread_self())<<" start working...\n";
        pthread_mutex_unlock(&pool->mutexPool);


        //调用函数
        task.function(task.arg);//?
        //printf("task.arg = %p \n", task.arg);
        delete task.arg;                       //*任务函数传的参数是堆内存
        //!这里free的是num
        task.arg=nullptr;


        pthread_mutex_lock(&pool->mutexPool);
        cout<<"thread "<<to_string(pthread_self())<<" end working...\n";//做完之后 忙线程-1
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexPool);
    }
    return NULL;
}

template <typename T> 
void* ThreadPool<T>::manager(void* arg)
{
    ThreadPool* pool=static_cast<ThreadPool*>(arg);
    while(!pool->shutdown){
        //3秒检测一次
        sleep(3);
        //取数据
        //加锁 在读这些数据时 可能别的线程在写这些数据
        
        //保护了整个线程池
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize=pool->taskQ->taskNumber();
        int liveNum=pool->liveNum;
        int busyNum=pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);

        
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

template <typename T> 
void ThreadPool<T>::threadExit()
{
    pthread_t tid=pthread_self();
    for(int i=0;i<maxNum;i++){
        if(threadIDs[i]==tid){
            threadIDs[i]=0;
            cout<<"thread "<<to_string(tid) <<" exit...\n";
            break; 
        }
    }
    pthread_exit(NULL);
}

