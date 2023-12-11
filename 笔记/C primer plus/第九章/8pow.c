//pow改进
//!注意0的n次幂为0
//!n的零次幂为1
#include<stdio.h>
#include<math.h>

double poow(double a,int n){
    double res=1;
    int i;
    if(a==0){
        res=0;
    
    if(n==0){
        res=1;
    }else{
        if(n>0){
            for(i=0;i<n;i++){
                res=res*a;
            }
        }else{
            for(i=n;i<0;i++){
                res=res*a;
            }res=1/res;
        }
    }
    }

    return res;
}
int main(){
    double a;
    int n;
    scanf("%lf %d",&a,&n);

    printf("%lf",poow(a,n));

    return 0;
}