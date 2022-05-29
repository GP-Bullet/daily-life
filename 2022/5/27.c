#include<stdio.h>

int gen(){
    static int j=-1;
    static int num1=0;
    static int num2=0;
    if(j==-1){j++;return j;}
    if(j==0){j++;return j;}
    if(j==1){num1++;}
    if(j==1&&num1%2==1){j++;return j;}
    if(j==1&&num1%2==0){j--;return j;}
    if(j==2){num2++;}
    if(j==2&&num2%2==1){j++;return j;}
    if(j==2&&num2%2==0){j--;return j;}
    if(j==3){j--;return j;}
}
int main(){
    int val,gen();
    int k=0;
    printf("Signal is:\n");
    for(;;)
    {
        if(k>2)break;
        val=gen();
        printf("%d \n",val);//这里的*去掉了
        if(val==0)k++;

    }
    return 0;
}