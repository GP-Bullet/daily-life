#include<stdio.h>

//四位水仙花数
int main(){
    int i;
    int a,b,c,d;
    for(i=1000;i<=9999;i++){
        d=i%10;
        c=i/10%10;
        b=i/10/10%10;
        a=i/1000;
        if(a*a*a*a+b*b*b*b+c*c*c*c+d*d*d*d==i){
            printf("%d\n",i);
        }
    }
    return 0;
}