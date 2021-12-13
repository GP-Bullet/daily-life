#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//带最大字符数
void func(char* a,int n){
    char ch;
    int i=0;
    while((ch=getchar())<=' '){
        continue;
    }
    while(ch>' ' && i<n){
        *a=ch;
        i++;
        a++;
        ch =getchar();
    }

}
int main(){
    int n;
    scanf("%d",&n);
    char a[n+1];
    func(a,n);
    puts(a);

    return 0;
    
}