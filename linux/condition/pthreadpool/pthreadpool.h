#ifndef _THREADPOOL_H
#define _THREADPOOL_H


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct ThreadPool ThreadPool;
//创建线程池并初始化
ThreadPool*  ThreadPoolCreate(int min,int max,int queSize);

//销毁线程池
int threadPoolDestory(ThreadPool*pool);
//给线程池添加任务
void threadPoolAdd(ThreadPool*pool,void(*func)(void*),void*arg);
//获取线程池中工作的线程的个数
int threadPoolBusyNum(ThreadPool*pool);
//获取线程池中的活着的线程的个数
int threadPoolAliveNum(ThreadPool*pool);

//
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);

#endif  