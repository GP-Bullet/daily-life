/*


*内存泄漏的解决方法
    内存泄漏（Memory Leak）是指程序中已动态分配的堆内存由于某种原因程序未释放或无法释放
*到底选用c库函数还是系统函数
*如何自己解决问题（具体）
查man手册
怎么看源码看不懂
怎么去搜谁想看的东西

*string buffer 和ls的开源
*位操作的妙用{还有哪些妙用}
这样就用简单的一个int型的数代替了复杂的指针数组。

!知识类
    *strcpy he memcpy
    各命令信息
    *argv[1]="abcde"
    argv[1][0]='-'

    *所占块
    *为啥有那么多头文件

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(){
    char c[10];
    printf("请输入一个运算符:");
    scanf("%s",c);
    if(c[0]=='+'||c[0]=='-'||c[0]=='*'||c[0]=='%'||c[0]=='/'){
        printf("请输入两个操作数:");
        float a,b;
        scanf("%f%f",&a,&b);
        switch(c[0]){
            case '+':
                printf("%f+%f=%.2f",a,b,a+b);
                break;
            case '-':
                printf("%f-%f=%.2f",a,b,a-b);
                break;
            case '*':
                printf("%f*%f=%.2f",a,b,a*b);
                break;
            case '/':
                    if(b==0){
                        printf("0不能做除数");break;
                    }else{
                        printf("%f/%f=%.2f",a,b,a/b);
                        break;
                    }
                    
            case '%':
                printf("%d%%%d=%d",(int)a,(int)b,(int)a%(int)b);
                break;
        }
    }else{
        printf("请输入一个操作数:");
        float d;
        scanf("%f",&d);
        if(strcmp("sin",c)==0){
            printf("sin%f=%.2f",d,sin(d));
        }else if(strcmp("cos",c)==0){
            printf("cos%f=%.2f",d,cos(d));
        }else if(strcmp("tan",c)==0){
            printf("tan%f=%.2f",d,tan(d));
        }else if(strcmp("exp",c)==0){
            printf("exp(%f)=%.2f",d,exp(d));
        }else if(strcmp("sqrt",c)==0){
            printf("sqrt%f=%.2f",d,sqrt(d));
        }
    }
    return 0;
}