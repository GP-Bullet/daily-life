#include <stdio.h>
void input(int a[], int *m)
{
    int x = 0;
    printf("请输入一批正整数：\n");
    do{
        scanf("%d", &a[x++]);
    } while (getchar() != '\n');
    *m = x;
}
int average(int a[], int m)
{
    int i;
    double sum = 0.0, t;
    for (i = 0; i < m; i++)
        sum += a[i];
    t = sum / m;
    return t;
}
int big(int a[], int m)
{
    int i, max = 0;
    for (i = 0; i < m - 1; i++)
        if (a[max] < a[i + 1])
            max = i + 1;
    return a[max];
}
int small(int a[], int m)
{
    int i, min = 0;
    for (i = 0; i < m - 1; i++)
        if (a[min] > a[i + 1])
            min = i + 1;
    return a[min];
}
int main()
{
    int m = 0, t, b, s;
    int a[100];
    input(a, &m);
    t = average(a, m);
    b = big(a, m);
    s = small(a, m);
    printf("平均值为:%d\n最大值为:%d\n最小值为:%d\n", t, b, s);
}