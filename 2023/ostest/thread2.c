#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100 // 数组元素个数

int sum = 0; // 全局变量，用于存储数组元素的加法和
pthread_mutex_t mutex; // 全局变量，用于创建和操作互斥锁


void *thread_func(void *arg)
{
    int i;
    int *p = (int *)arg; // 强制转换为int类型指针
    for (i = 1; i <= N / 2; i++)
    {
        pthread_mutex_lock(&mutex); // 获取互斥锁
        sum += p[i]; // 将数组元素加到sum上
        pthread_mutex_unlock(&mutex); // 释放互斥锁
    }
    return NULL;
}

int main()
{
    int i;
    int *array = malloc(N * sizeof(int)); // 动态分配一个大小为N个int类型元素的数组
    for (i = 1; i <= N; i++)
    {
        array[i] = i; 
        printf("a[%d]=%d\n",i,i);
    }

    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    pthread_t tid1, tid2; 

    pthread_create(&tid1, NULL, thread_func, array); // 创建第一个线程，并将array作为参数传递给它
    pthread_create(&tid2, NULL, thread_func, array + N / 2); // 创建第二个线程，并将array + N / 2作为参数传递给它

    pthread_join(tid1, NULL); 
    pthread_join(tid2, NULL); 

    printf("sum = %d\n", sum); 

    free(array); 
    pthread_mutex_destroy(&mutex); // 销毁互斥锁

    return 0;
}