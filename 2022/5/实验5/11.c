//N位水仙花数
/*
升级版，输出N位水仙花数
水仙花数是指一个N位正整数(N≥3),它的每个位上的数字的N次幂之和等于它本身
*/
#include <stdio.h>

int p(int a, int b);//计算a的b次幂

int main(void)
{
    int n,t = 0;
    scanf("%d", &n);
    //得到水仙花数的上下限
    int down = p(10, n - 1);
    int up = p(10, n);
    for (int i = down; i < up; i++)
    {
        int k = i;
        int sum = 0;
        while (k > 0)  //计算i每位上的数字的N次幂之和
        {
            t = k % 10;
            k = k / 10;
            sum += p(t, n);
        }
        if(sum == i)
            printf("%d\n", i);
    }

    return 0;
}
int p(int a, int b)
{
    int t = a;
    for (int i = 1; i < b; i++)
        a = a * t;

    return a;
}