#include<stdio.h>

#define SIZE 5

int formax(int *,int *);
int main(void){
    int  a_max;
    int a[SIZE]={1,4,5,3,2};
    a_max=formax(a,a+SIZE);
    printf("%d",a_max);

    return 0;
}

int formax(int * p1,int *p2){
    int max=*p1;
    for(;p1<p2;p1++)
        if(max<*p1)
            max=*p1;
    return max;
}


