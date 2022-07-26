#pragma once
#include<queue>
#include<pthread.h>
using namespace std;
using callback =void (*)(void* arg);

//模板
template <typename T>
struct Task
{
    Task<T>()
    {
        function=nullptr;
        arg=nullptr;
    }
    Task<T>(callback f,void *arg)
    {
        this->arg=(T*)arg;
        function=f;
    }
    callback function;//保存地址
    T* arg;//保存实参地址
} ;

template <typename T>
class TaskQueue
{
public:
    TaskQueue()
    {
        pthread_mutex_init(&m_mutex,NULL);
    }
    ~TaskQueue()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    //添加任务
    void addTask(Task<T> task)
    {
        pthread_mutex_lock(&m_mutex);
        m_taskQ.push(task);
        pthread_mutex_unlock(&m_mutex);
    }
    void addTask(callback f,void*arg)
    {
        pthread_mutex_lock(&m_mutex);
        m_taskQ.push(Task<T>(f,arg)); 
        pthread_mutex_unlock(&m_mutex);
    }
    //取出一个任务
    Task<T> takeTask()
    {   
        Task<T> t;
        pthread_mutex_lock(&m_mutex);
        if(!m_taskQ.empty()){
            t=m_taskQ.front();
            m_taskQ.pop();
        }
        pthread_mutex_unlock(&m_mutex);
        return t;
    }
    //获取当前任务的个数
    inline size_t  taskNumber()//内联
    {
        return m_taskQ.size();
    }
private:
    queue<Task<T>> m_taskQ;
    pthread_mutex_t m_mutex;
};