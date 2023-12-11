//输出n以内的所有素数

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int is_prime(int n)
{
	for(int i=2; i<=(int)sqrt(1.0*n); i++)
	{
		if(n%i == 0)
			return 0;
	}
	return 1;
}
int main()
{
	int n,i,j=0;
	printf("请输入n的值:\n");
	scanf("%d",&n);
	printf("小于等于%d的素数有:\n",n);
	if(n<2)
    {
		printf("没有素数");
        return 0;
    }
	if(n==2)
	{
		printf("%4d\n",n);
		return 0;
	}
    printf("%4d\t",2);
    j++;
	for(i=3;i<=n;i+=2)//除了2其余的任何素数都不会有偶数 
	{ 
		if(is_prime(i)==1) 
		{
			printf("%4d\t",i);
			j++; 
			if(j%5==0) 
				printf("\n");
		}
	} 
	printf("\n");

    return 0;
}