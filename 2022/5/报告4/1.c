#include<stdio.h>
int main(void)
{
    int a[10]={0},max=0,t=0;
    double sum;
    for (int i=0; i<10; i++)
    {
        scanf("%d",&a[i]);
        if(max < a[i])
        {
            max = a[i];
            t=i+1;
        }
        sum += a[i];
    }
    printf("成绩最高者的序号为%d,其成绩为%d.\n平均成绩为%.3lf.\n",t,max,sum/10);
    return 0;
}