#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int i,a,sum;
    for(i=0;i<n;i++){
        scanf("%d",&a);
        if(i==0)sum=a;
        else sum=sum^a;
    }
    printf("%d",sum);
    return 0;
    

}