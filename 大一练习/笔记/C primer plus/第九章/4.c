#include<stdio.h>
double avg(double a,double b){//注意写类型
    return a=1/(0.5*(1/a+1/b));
}
int main(){
    double a,b;
    scanf("%lf %lf",&a,&b);
    printf("%lf",avg(a,b));//可在此用

    return 0;
}