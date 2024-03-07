#include<stdio.h>	

void swap(int *a,int *b){
    *a=7;
    *b=5;
}

int main(){
    int a=5,b=7;
    printf("%d %d\n",a,b);
    printf("%p %p\n",&a,&b);
    swap(&a,&b);
    printf("%d %d\n",a,b);
    printf("%p %p\n",&a,&b);
    return 0;
}