#include<stdio.h>

double min(double x,double y);
int main(){
    double x,y;
    scanf("%lf %lf",&x,&y);
    
    x=min(x,y);
    printf("%lf",x);
    return 0;
}

double min(double x,double y){
    return x<y?x:y;
}