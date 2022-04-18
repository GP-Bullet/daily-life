#include<stdio.h>
int main(){
    int m,n,i;
    scanf("%d %d",&n,&m);
    int a[200];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<m;i++){
        a[n+i]=a[i];
    }
    for(i=0;i<n;i++){
        a[i]=a[m+i];
    }
    for(i=0;i<n;i++){
        if(i){
            printf(" ");
        }
        printf("%d",a[i]);
    }
    return 0;
}
