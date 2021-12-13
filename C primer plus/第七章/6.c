#include<stdlib.h>
#include<stdio.h>

//ei两个字符出现的次数
//?break    

int main(){
    char pre,ch;
    int n=0;
    while(pre=getchar()!='#'){
        if(pre=='e'){
            ch=getchar();
            if(ch=='i'){
                n++;
                continue;
            }
        }
    }
    printf("%d",n);
    return 0;
}