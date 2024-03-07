//!注意用return的区别
//!用太多return容易乱
#include<stdio.h>

double poow(double a,int n){
    double res=1;
    
    if(a==0){
        if(n==0){
            return 1;
        }
        return 0;
    }
    
    if(n==0){
        return 1;
    }

    if(n>0){
        return res*poow(a,n-1);
    }else{
        return 1/(res*poow(a,n+1));
        }

}
    


int main(){
    double a;
    int n;
    scanf("%lf %d",&a,&n);

    printf("%lf",poow(a,n));

    return 0;
}