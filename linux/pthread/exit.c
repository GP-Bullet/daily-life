#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
void* thr_fn1(void *arg){
    printf("thread 1 returning\n");
    return (void*)1;
}
void* thr_fn2(void *arg){
    printf("thread 2 exiting\n");
    pthread_exit((void*)2);//线程结束
}
void* thr_fn3(void *arg){
    while(1){
        printf("thread 3 writing\n");
        sleep(1);
    }
}

int  main(void){
    pthread_t tid;
    void *tret;
    pthread_create(&tid,NULL,thr_fn1,NULL);
    pthread_join(tid,&tret);//回收线程,线程退出值保存在tret(二重指针)
    //前面没结束后面不能执行
    printf("thread 1 exit code %ld\n",(long)tret);


    pthread_create(&tid,NULL,thr_fn2,NULL);
    pthread_join(tid,&tret);
    printf("thread 2 exit code %ld\n",(long)tret);

    pthread_create(&tid,NULL,thr_fn3,NULL);
    sleep(3);
    pthread_cancel(tid);//主控线程去取消线程3
    //这里退出的宏应该PTHREAD_CANCELED
    
    pthread_join(tid,&tret);
    printf("thread 3 exit code %ld\n",(long)tret);

    return 0;
}