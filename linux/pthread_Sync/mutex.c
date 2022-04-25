#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM 5000

int counter;
pthread_mutex_t counter_mutex=PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);
int main(){
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,doit,NULL);
    pthread_create(&tid2,NULL,doit,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;
}

void *doit(void *vptr){
    int i,val;
    for(i=0;i<NUM;i++){
        pthread_mutex_lock(&counter_mutex);
        val=counter;
        printf("%x: %d\n",(unsigned int)pthread_self(),val+1);
        counter=val+1;

        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}