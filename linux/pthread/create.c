#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//-lpthread 线程库的函数 链接
void *th_fun(void*arg){
    int *p=(int *)arg;

    printf("thread PID=%d\n",getpid()); //线程里面的进程号
    printf("thread ID=%x\n",(unsigned int)pthread_self()); //线程里面的线程号
    printf("thread *arg =%d\n",*p);

    
   // while(1);
}

int main(){
    pthread_t tid;
    int n=10;

    pthread_create(&tid,NULL,th_fun,(void*)&n);
    sleep(1);
    printf("main thread ID=%x\n",(unsigned int)pthread_self());//主控线程号
    printf("main child thread ID=%x\n",(unsigned int)tid);//主控线程的线程号
    printf("main PID=%d\n",getpid());//主控线程的进程号
    
  //  while(1);
    return 0;
}