#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//?素数,只接受正整数输入
//?memset
int main(){
    long long num;
    int x=1;
    long long a[num];
    int i,j;
    while(x){
        if(scanf("%lld",&num)==1){
            if(num<1){
                continue;
            }else{
                x=0;
                const int len=num;
                int a[len+1];
                memset(a,0,sizeof(int)*(len+1));
                for(int i=2;i<=num;i++){
                    if(!a[i]){
                        for(int i=2;i<=num;i++){
                            a[j]=1;
                            }
                        }
                    }
                }
                for(int i=2;i<=num;i++){
                    if(!a[i]){
                        printf("%d ",i);
                    }
                }
                printf("\n");
            }
        }
        return 0;
    }
    
