//4
#include<stdio.h>
int main(void)
{
    int a[100]={0},b[100]={0},c[100]={0};
    int n=0,m=0;
    printf("请输入两个升序数列\n");
    do{
        scanf("%d",&a[n++]);
    } while (getchar()!='\n');

    do{
        scanf("%d",&b[m++]);
    } while (getchar()!='\n');

    int t=0;
    int i=0,j=0;
    while(i<n && j<m)
    {

        if(a[i]>=b[j])
            c[t++] = b[j++];
        else
            c[t++] = a[i++];    
    }   

    if(i==n)
        while(t<n+m)
            c[t++] = b[j++];
    else
        while(t<n+m)
            c[t++] = a[i++];


    printf("升序合并后的数列为:\n");
    for(int i=0; i<t; i++)
    {
        printf("%d",c[i]);
        if(i!=t-1)
            printf(",");
        else
            printf("\n");
    }
    return 0;
}