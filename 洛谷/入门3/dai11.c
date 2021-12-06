#include<stdio.h>
int main(){
    int n,i;
    int count=0;
    int a[10000];
    scanf("%d",&n);
    for(i=0;i<n;i++){
    scanf("%d ",&a[i]);    
    }
    for(i=0;i<n;i++){
        if(a[i+1]==a[i]){
            count++;
        }else{
            count=0;
        }        
}
    printf("%d",count);

    return 0;
}
