#include<stdio.h>
#include<stdlib.h>
#include<string.h>//?
#include<ctype.h>//?

//!跳空白、制表符、换行符

void func(char*a){
    char ch;
    while((ch=getchar())<=' '){
        continue;
    }
    while(ch > ' '){
        *a=ch;
        a++;
        ch =getchar();

    }
}

int main(){
    char a[101];
    func(a);
    puts(a);

    return 0;
}

