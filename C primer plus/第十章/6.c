//倒序排列
#include<stdio.h>
#define size 5
int main(){
    double a[size]={1.1,3.1,5.1,2.1,2.2};
    double a=func(a);
    for(int i=0;i<size;i++){
        printf("%lf",a[i]);
    }
    return 0;
}

double func(double *p){
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n-1;j++){
            if(*p<*p++){
                p++=*p;
                
            }
        }
    }
}