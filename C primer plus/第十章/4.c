#include<stdio.h>
#define size 5
int formax(double *p1,int p2){
    int max=0;
    //!用i来记录下标
    int i;
    for(i=1;i<size;i++){
        if(*(p1+max)<*(p1+i))
        max=i;
    }
    return max;
}


int main(){
    int max;
    double a[size]={1.1,5.1,2.1,2.1,3.1};
    max=formax(a,size);
    printf("%d",max);


    return 0;
}