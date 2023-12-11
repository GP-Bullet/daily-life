#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct grade//结构体记录一个人的成绩和序号
{
    int num;
    int score;
}a[100];

int cmp(const void*a,const void*b)
{
    if(((struct grade*)a)->score != ((struct grade*)b)->score)
        return ((struct grade*)b)->score - ((struct grade*)a)->score;
    else
        return ((struct grade*)a)->num - ((struct grade*)b)->num;
}

int main(void)
{
    int n=0,r=0;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d",&a[i].score);
        a[i].num = i+1;
    }

    qsort(a,n,sizeof(a[0]),cmp);
    //打印输出，t用来存成绩相等的人数（每次出现不相等的则置为0）
    int t=0;
    for(int i=0; i<n;i++)
    {
        if(a[i-1].score == a[i].score && i>0)
        {
            printf("%d:%d,%d\n",i-t,a[i].num,a[i].score);
            t++;
        }
        else
        {
            printf("%d:%d,%d\n",i+1,a[i].num,a[i].score);
            t=0;
        }
    }
    return 0;
}