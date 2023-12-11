#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void*a,const void*b)
{
    return strcmp((char*)a,(char*)b);
}
int main(void)
{
    char a[6][100]={0};
    printf("请输入6个字符串:\n");
    for(int i=0; i<6; i++)
    {
        scanf("%s",a[i]);
    }

    qsort(a,6,100,cmp);
    printf("按字典序排序后为:\n");
    for(int i=0; i<6; i++)
    {
        printf("%s\n",a[i]);
    }
    return 0;
}