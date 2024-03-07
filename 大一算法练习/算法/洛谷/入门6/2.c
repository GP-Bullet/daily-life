//质数筛
//80
#include<stdio.h>
#include<math.h>

//
int zhishu(int n);

int main(){
    int n,i,j=0;
    int sum=0;
    scanf("%d",&n);
    int a[101];
    int b[101];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        if(zhishu(a[i])){
            b[j++]=a[i];
            sum++;
        }

    }
    
    for(i=0;i<sum;i++){
        printf("%d ",b[i]);
    }

    return 0;
}

int zhishu(int n){
    if(n==2||n==3){
        return 1;
    }
    if(n%6!=1 && n%6!=5){
        return 0;
    }
    for(int i=5;i<=sqrt(n);i+=6){
        if(n%i==0||n%(i+2)==0){
            return 0;
        }
    }

    return 1;
}