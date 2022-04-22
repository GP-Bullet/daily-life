#include<stdio.h>
int main(){
    int a[2000];
    int i,j;
    int max,min;
    int n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",& a[i]);
    }

    max=a[0];
    min=a[0];
    for(j=0;j<n;j++){
        if(max<a[j])max=a[j];
        if(min>a[j])min=a[j];
    }

    
    printf("%d",max-min);
    return 0;
}