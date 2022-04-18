#include<stdio.h>
#include<unistd.h>
int main(void){
    int counter;
    alarm(1);
    for(counter=0;1;counter++){
        printf("counter=%d ",counter);
    }
    return 0;
}