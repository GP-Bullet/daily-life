#include<stdio.h>
#define SIZE 4
void sum1(double *p1, double *p2, double *p3,int n);
void pr(double *p,int n);
int main(){
    double arr1[SIZE] = {2, 4, 5, 8};
    double arr2[SIZE] = {1, 0, 4, 6};
    double sum[SIZE];

    sum1(arr1,arr2,sum,SIZE);
    pr(sum,SIZE);

    return 0;
}

void sum1(double *p1,double *p2,double *p3,int n){
    int i;
    for(i=0;i<n;i++){
        p3[i]=p1[i]+p2[i];
    }
}

void pr(double*p,int n){
    int i;
    for(i=0;i<n;i++,p++){
        printf("%.1lf",*p);
        printf("\n");
    }
}
