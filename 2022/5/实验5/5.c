/*
求两个正整数最大公约数和最小公倍数
用欧几里德算法(辗转相除法)求两个数的最大公约数
两个正整数的最小公倍数=两个数的乘积/两个数的最大公约数
*/
#include<stdio.h>

int func1(int a, int b)
{
    int t, r;
    if (b > a)
    {
        t = a;
        a = b;
        b = t;
    }
    while ((r = a % b) != 0)
    {
        a = b;
        b = r;
    }
    return b;
}

int func2(int a, int b, int c)
{
    return (a * b / c);
}

int main()
{   //a,b为输入的两个数，c为最大公约数，d为最小公倍数
    int a, b, c, d;
    scanf("%d,%d", &a, &b);

    c = func1(a, b);
    printf("这两个数的最大公约数为：%d\n", c);
    d = func2(a, b, c);
    printf("这两个数的最小公倍数为：%d\n", d);

    return 0;
}