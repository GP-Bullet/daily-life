//?
#include<stdlib.h>
#include<stdio.h>


//?求模运算

int main(){
    char ch;
    int t=1;
    while((ch=getchar()) != '#'){
        putchar(ch);
        printf("%d ",ch);
        if(!(t++ % 8)){
            printf("\n");
        }
    }
    return 0;
}