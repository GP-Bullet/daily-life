#include<stdio.h>
int main(){
    int i,b,j;
    int a[10];
    for(i=0;i<10;i++){              
        scanf("%d ",&a[i]);
    }
    scanf("%d",&b);

    int count=0;
    for(j=0;j<10;j++){
        if(a[j]<=b+30){
            count++;
        }
    }
    printf("%d",count);

    return 0;

}