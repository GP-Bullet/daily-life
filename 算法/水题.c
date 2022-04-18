#include<stdio.h>
int main(){
    int n,k,t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(n<=k)
            printf("%d\n",k-n);
        else{
            if((n-k)&1){
                printf("1\n");
            }
            else printf("0\n");
        }
    }
    return 0;
    
}