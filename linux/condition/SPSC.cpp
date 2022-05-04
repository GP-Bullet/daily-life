  //这是生产者消费者模型的代码                                                                                                                   
#include<iostream>
#include<queue>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 8  


class BlockQueue
{
    private:
    std::queue<int> q;
    int cap;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;

    private:
      void LockQueue()  //队列加锁
    {
        pthread_mutex_lock(&mutex);
    }
      void UnlockQueue()  //队列解锁
    {
        pthread_mutex_unlock(&mutex);
    }
      void ProductWait()  //队列满，生产者等待
    {
        pthread_cond_wait(&full,&mutex);
    }
      void ConsumeWait()  //队列空，消费者等待
    {
        pthread_cond_wait(&empty,&mutex);
    }
      void NotifyProduct()  //队列不为满时，通知生产者
    {
        pthread_cond_signal(&full);
    }
      void NotifyConsume()  //队列不为空时，通知消费者
    {
        pthread_cond_signal(&empty);
    }
    bool IsEmpty()
    {
        return (q.size() == 0 ? true : false);
    }
    bool IsFull()
    {                                                                                                                                          
	return (q.size() == cap ? true : false);
    }
    public:
      BlockQueue(int _cap = NUM):cap(_cap) //构造函数
    {
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&full,NULL);
        pthread_cond_init(&empty,NULL);
    } 
    void PushData(const int &data)
    {
        LockQueue();
        while(IsFull()) //队列满
        {
        NotifyConsume();
        std::cout<<"queue full,notify consume data,product stop!!"<<std::endl;
        ProductWait();
        }
        //队列不满,生产者插入数据，通知消费者队列中已经有数据了
        q.push(data);
        NotifyConsume();
        UnlockQueue();
    }
    void PopData(int &data)
    {                                                                                                                                          
        LockQueue();
        while(IsEmpty())  //队列为空
        { 
        NotifyProduct();
        std::cout<<"queue empty,notify product data,consume stop!!"<<std::endl;
        ConsumeWait();
        }
        //队列不为空
        data = q.front();
        q.pop();
        NotifyProduct();
        UnlockQueue();
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
    }
};

  //消费者
void* consumer(void* arg)
{
    BlockQueue *bqp = (BlockQueue*)arg;
    int data;
    for(;;)                                                                                                                                      
    {
    bqp->PopData(data);
    std::cout<<"Consume data done: "<<data<<std::endl;
    }  }

  //生产者
void* producter(void* arg)
{
    BlockQueue *bqp = (BlockQueue*)arg;
    srand((unsigned long)time(NULL));
    for(;;)
    {
    int data = rand()%1024;
    bqp->PushData(data);
    std::cout<<"Product data done: "<<data<<std::endl;
     // sleep(1);
    }
}

int main()
{
    BlockQueue bq;
    pthread_t c,p;

    pthread_create(&c,NULL,consumer,(void*)&bq);
    pthread_create(&p,NULL,producter,(void*)&bq);
                        
    pthread_join(c,NULL);
    pthread_join(p,NULL);

    return 0;
}

