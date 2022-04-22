#include<stdio.h>
//!输出的全为a[0];
void copy_arr(double a[5],double b[5],int n){
    int i;
    for(i=0;i<n;i++){
        a[i]=b[i];
    }
}



void copy_ptr(double *p1,double *p2,int n){
    int i;
    for(i=0;i<n;i++,p1++,p2++){
        *p1=*p2;
    }
}

void copy_ptrs(double *p1,double *p2,double *p3){
    for(;p1<p2;p1++){
        *p1=*p2;
    }
}






int main(){
    double source[5]={1.1,2.2,3.3,4.4,5.5};
    double target1[5];
    double target2[5];
    double target3[5];

    
    copy_arr(target1,source,5);
    copy_ptr(target2,source,5);
    copy_ptrs(target3,source, source+5);

    for(int i=0;i<5;i++){
        printf("%.1lf %.1lf %.1lf",target1[i],target2[i],target3[i]);
        printf("\n");
    }

    return 0;
}

