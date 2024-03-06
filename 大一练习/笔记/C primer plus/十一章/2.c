#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//getchar一系列
void func(char* a,int n){

    int i;
    for(i=0;i<n;i++){
        a[i]=getchar();
        if(a[i]<=' '){//?为啥小于等于
            break;
        }
    }
    a[i]='\0';
}

int main(){
    int n;
    scanf("%d",&n);
    getchar();
    char a[n+1];
    func(a,n);
    puts(a);

    return 0;
}
