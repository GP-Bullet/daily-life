#include <stdio.h>
#include <math.h>

int is_prime(int t)
{
    for (int i = 2; i <= sqrt(1.0 * t); i++)
        if (t % i == 0)
            return 0;
    return 1;
}
int main(void)
{
    int a[2000] = {2, 0};
    int n = 1;
    for (int i = 3; i < 1994; i++)
        if (is_prime(i))
            a[n++] = i;

    int c = 0, d = 0;
    int mark = 0;
    for (int i = n - 1; i >= 0; i--)
        if (a[i] < 1898)
        {
            c = i + 1;
            break;
        }

    for (int i = 0; i < n; i++)
        if (a[i] > a[n - 1] - 1898)
        {
            d = i - 1;
            break;
        }
        
    for (int i = c; i < n - 1; i++)
        for (int j = 0; j <= d; j++)
            if (a[i] - a[j] == 1898)
            {
                mark++;
                printf("%d-%d\n",a[j],a[i]);
            }

    if (mark != 0)
        printf("有%d种这样的数列,他们的和是1898\n", mark);
    else
        printf("没有这样的数列,他们的和是1898\n");

    return 0;
}