#include<stdio.h>
//4  3位水仙花
int main(){
    int i;
    int a,b,c,d;
    for(i=100;i<=999;i++){
        c=i%10;
        b=i/10%10;
        a=i/100;
        if(a*a*a+b*b*b+c*c*c==i){
            printf("%d\n",i);
        }
    }
    return 0;
}