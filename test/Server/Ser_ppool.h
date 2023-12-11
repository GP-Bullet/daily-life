#pragma once
#include"Ser_task.hpp"
template <typename T> 
class ThreadPool
{
public:
    //创建线程池并初始化
    ThreadPool(int min,int max);

    //销毁线程池
    ~ThreadPool();

    void addTask(Task<T> task);

    //获取忙的线程个数
    int getBusyNum();
    
    //获取活着的线程个数
    int getLiveNum();

private:
    //消费者任务函数
    static void*worker(void*arg);
    //管理者任务函数
    static void*manager(void*arg);
    //单个线程退出
    void threadExit();

private:
    //任务队列
    TaskQueue<T>* taskQ;

    pthread_t managerID;  //管理者线程ID
    pthread_t *threadIDs;  //工作的线程ID
    int minNum;             //最小线程数量
    int maxNum;             //最大线程数量
    int busyNum;            //忙
    int liveNum;            //存活的
    int exitNum;            //销毁

    pthread_mutex_t mutexPool;  //锁整个线程池
    //busyNum 发生变化大
   // pthread_mutex_t mutexBusy;
    pthread_cond_t notEmpty; //任务队列是否空

    static const int NUMBER=2;
    int shutdown;   //是不是要销毁销毁线程池，销毁为1，不销毁为0
};