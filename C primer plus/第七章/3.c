#include<stdio.h>
#include<stdlib.h>

//用什么输入呢

int main(){
    char ch;
    int o=0,j=0,os=0,js=0;
    double osa=0.0,jsa=0.0;
    int a;

    while(scanf("%d",&a)&&a){//利用本身的1和0
        if(a%2){
            j++;
            js+=a;
        }else{
            o++;
            os+=a;
        }
    }
    if(o){
        osa=(double)os/(double)o;
    }
    if(j){
        jsa=(double)js/(double)j;
    }

    printf("%d %.2lf   %d  %.2lf\n",o,osa,j,jsa);

    return 0;
}