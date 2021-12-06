#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int a,b,c,d,e,f;
    scanf("%d %d",&a,&b);
    scanf("%d %d",&c,&d);
    scanf("%d %d",&e,&f);
    int p1,p2,p3;

    p1=(n/a+1)*b;
    p2=(n/c+1)*d;
    p3=(n/e+1)*f;

    int t;
    if(p1>p2){
        t=p1;
        p1=p2;
        p2=t;
    }
    if(p1>p3){
        t=p1;
        p1=p3;
        p3=t;
    }
    if(p2>p3){
        t=p2;
        p2=p3;
        p3=t;
    }
    printf("%d",p1);

    return 0;
    
}