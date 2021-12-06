#include<stdio.h>
void copy(double *p1,double *p2,int n);
int main(){
    int i;
    double a[7]={1.1,2.2,3.3,4.4,5.5,6.6,7.7};
    double b[3];
    copy(b,a+2,3);//!或者&a[2]
    for(i=0;i<3;i++) {
        printf("%.1lf",b[i]);
        printf("\n");
    }   
    return 0;
}

void copy(double *p1,double *p2,int n){
    int i;
    for(i=0;i<n;i++,p1++,p2++){
        *p1=*p2;
    }
}
