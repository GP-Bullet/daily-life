#include<stdio.h>
int main(){
    int n;
    double p;
    
    scanf("%d",&n);

    if(n<=150){
        p=0.4463*n;
    }
    if(150<n<401){
        p=0.4463*150+0.4663*(n-150);
    }
    if(n>=401){
        p=0.4463*150+0.4663*250+0.5663*(n-400);
    }
    printf("%.1lf",p);

    return 0;
}
