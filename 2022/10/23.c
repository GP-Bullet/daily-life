#include<stdio.h>
int main(){
    int *b=(int *)2;
    int *a=b;
    printf("%d\n",a+3);
    printf("%d\n",a);
    printf("%d\n",a+1);

}