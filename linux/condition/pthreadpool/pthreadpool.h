#ifndef _THREADPOOL_H
#define _THREADPOOL_H


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct ThreadPool ThreadPool;
//创建线程池并初始化
ThreadPool*  ThreadPoolCreate(int min,int max,int queSize);

//销毁线程池

//给线程池添加任务

//获取线程池中工作的线程的个数

//获取线程池中的活着的线程的个数


#endif  