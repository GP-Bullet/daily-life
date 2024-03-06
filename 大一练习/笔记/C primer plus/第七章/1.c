#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//switch条件
int main(){
    char ch;
    int a=0,b=0,c=0;
    while((ch=getchar()) !='#'){//while循环的使用，一般是有个限制条件，否则一直循环
        switch(ch){
            case' ':
                a++;
                break;
            case'\n':
                b++;
                break;
            default://其他字符
                c++;
        }
    }

    printf("%-5d %-5d %-5d\n",a,b,c);//左对齐

    return 0;
}