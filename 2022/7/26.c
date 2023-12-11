#include<stdio.h>

int main(){
    int *pArr[3];
    int r1[]={1};
    int r2[]={2,3};
    int r3[]={4,5,6};
    pArr[0]=r1;
    pArr[1]=r2;
    pArr[2]=r3;
    
    printf("%d\n",pArr[2][1]);
}