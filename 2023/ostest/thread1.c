#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* myfunc(){
    int i;
    for(i=1;i<=500;i++){
        printf("%d\n",i);
    }
}

int main(){
    pthread_t th1,th2;
    pthread_create(&th1,NULL,(void*)myfunc,NULL);
    pthread_create(&th2,NULL,(void*)myfunc,NULL);
    
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    return 0;
}
