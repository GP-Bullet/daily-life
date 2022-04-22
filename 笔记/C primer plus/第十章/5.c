//!复习求最大值和最小值的几种方法

#include<stdio.h>
#define size 5
double func(double *p,int n){
    double max=*p;
    double min=*p;
    int i;
    for(i=1;i<n;i++){
        if(max<*(p+i))max=*(p+i);
        if(min>*(p+i))min=*(p+i);
    }
    return max-min;
}


int main(){
    double cha;
    double a[size]={2.1,4.1,6.1,1.1,9.1};   
    cha=func(a,size);
    printf("%lf",cha);

    return 0;
}