//质数筛
#include<stdio.h>
int zhishu(int a[0]); 

int main(){
    int n,i;
    scanf("%d",&n);
    int a[n];
    int b[n];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    //判断质数
    for(i=0;i<n;i++){
        if(!(zhishu(a[i]))){
        a[i]=a[i+1];
        }
    }


    return 0;

}

int zhishu(int a[0]){
    int i;
    for(i=2;i<=a[i]-1;i++){
        if(a[i]%i==0)
        return 0;
    }
    return 1;
}