#include<stdio.h>
#include<string.h>
int main(void)
{
    int num[1000];
    int sum[1000],t;
    memset(num,0,1000);
    memset(sum,0,1000);

    for(int i = 1; i<1000; i++)
    {  
        t = 0;
        for(int n = 1; n<i; n++)
            if(i/n*n == i)
                num[t++] = n;
        
        for(int j = 0; j<t; j++)
            sum[i] += num[j];

        for(int j = 1; j<i; j++)
        {
            if(sum[i] == j && sum[j] == i)
                printf("%d和%d\n",j,i);
        }
    }

    return 0;
}   