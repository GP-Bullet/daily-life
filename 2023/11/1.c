#include <stdio.h>

struct migration_event {
    int pid;
};

void test(int *data){
    int a=data;
    printf("%d",a);
}

int main(){
    struct migration_event * event;
    event->pid=1;
}