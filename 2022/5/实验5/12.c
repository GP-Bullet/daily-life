#include<stdio.h>
int main(void)
{
    int n;
    scanf("%d",&n);
    for(int i = n-1; i > 1; i--)
    {
        if (i%2 != 0 && n%i == 0)
            if (n/i - i/2 > 0)
                printf("%d-%d\n",n/i - i/2, n/i + i/2);
        if (i%2 == 0 && n%i == i/2)
            if(n/i - i/2 + 1 > 0)
                printf("%d-%d\n",n/i - i/2 + 1, n/i + i/2);
    }
    return 0;
}