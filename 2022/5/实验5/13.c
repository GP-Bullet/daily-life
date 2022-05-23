#include <stdio.h>
int main()
{
    int n = 0, sum, max = 0;
    int a[100];
    do
    {
        scanf("%d", &a[n++]);
    } while (getchar() != '\n');

    for (int i = 0; i < n - 2; i++)
    {
        sum = a[i] + a[i + 1] + a[i + 2];
        if (sum > max)
            max = sum;
    }
    printf("%d\n", max);
    return 0;
}