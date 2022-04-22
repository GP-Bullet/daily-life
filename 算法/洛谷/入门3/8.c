#include<stdio.h>
int main(){
    int k,i;
    double sum=0.0;
    scanf("%d",&k);
    for(i=1;;i++){
        sum=sum+1.0/i;
        if(sum>k)break;
    }
    printf("%d",i);
    return 0;
}
//1.0000000与1的比较
//注意数据类型
