#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void func(char* a,int n){
    int i;
    for(i=0;i<n;i++){
        a[i]=getchar();
    }
    a[i]='\0';
}

int main(){
    int n;
    scanf("%d",&n);
    char a[n+1];
    
    func(a,n);
    puts(a);
    return 0;
}