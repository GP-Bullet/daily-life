//1 直接判断
#include<stdio.h>
#include<math.h>


int zhishu1(int n){

    for(int i=2;i<=n-1;i++){
        if(n%i==0)
        return 0;
    }
    return 1;
}

//2 sqrt
int zhishu2(int n){
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}

//3  6x+-1
int zhishu3(int n){
    if(n==2||n==3){
        return 1;
    }
    if(n%6!=1&&n%6!=5){
        return 0;
    }
    for(int i=5;i<+sqrt(n);i+=6){
        if(n%i==0||n%(i+2)==0)
        return 0;
    }

    return 1;
}