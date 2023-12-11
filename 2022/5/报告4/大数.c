#include<stdio.h>

int main(void)
{
    char a[201]={'\0'};
    char b[201]={'\0'};
    char c[201]={'\0'};
    c[201] = '\0';
    char ch = 0;
    int num_a=0,num_b=0;
    printf("请输入两个整数（不超过一百位）：\n");
    //读入两个数
    ch = getchar();
    while(ch!= '\n')
    {
        a[num_a++] = ch;
        ch = getchar();
    }   
    ch = getchar();         
    while(ch!= '\n')
    {
        b[num_b++] = ch;
        ch = getchar();
    }
    //数字右移并补零
    for(int i=0; i<num_a; i++)
        a[200-i] = a[num_a-i-1];
    for(int i=0; i<num_b; i++)
        b[200-i] = b[num_b-i-1];
    for(int i=100; i<=200-num_a; i++)
        a[i] = '0';
    for(int i=100; i<=200-num_b; i++)
        b[i] = '0';
    //相加运算
    int up =0;//记录进位
    int big = num_a > num_b ? num_a : num_b;
    for(int i=0; i<big+1; i++)
    {
        if((a[200-i]-'0' + b[200-i]-'0'+ up) == 10)//某位相加为10时要特殊考虑
        {
            c[200-i] = '0';
            up = 1;
        }
        else
        {
            c[200-i] = (a[200-i]-'0' + b[200-i] -'0')%10 + up + '0';
            up = 0;
            up = (a[200-i]-'0' + b[200-i]-'0')/10;
        }
    }

    //可以按照字符串输出
    if(c[200-big] == '0')
        printf("%s\n",&c[200-big+1]);
    else
        printf("%s\n",&c[200-big]);
}