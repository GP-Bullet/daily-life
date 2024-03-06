#if 0
void main()
{
	int k;
	char cp;
	//while(1 == scanf("%d",&a))
	//while((cp = getchar()) != '\n')
	cp = getchar();
	if(cp >= '0'&&cp <= '9')
		k = cp - '0';
	/*
	a  b  c  d  e  f
	10 11 12 13 14 15
	"1234"->1234 n = n *10 + c - '0'
	1234->"1234"
	十进制转换成二进制，八进制，十六进制
	十进制转换成任意进制
	任意进制转换成任意进制
	*/
	else if(cp >= 'a' && cp <= 'f')
		k = cp - 'a' + 10;
	else
		k  = cp - 'A' + 10;
	printf("k = %d\n",k);
}
#endif
//十进制转换成二进制和八进制
#if 1
#include<stdio.h>
int main()
{
	int a,b;//十进制和二进制或八进制
	int c[10]; //存储余数
	int i = 0;
	while(2 == scanf("%d%d",&a,&b))
	{
		i = 0;
		while(a != 0)
		{
			c[i] = a % b;
			a = a / b;
			i++;
		}
		//i表示的是个数
		i--;
		while(i >= 0)
		{
			printf("%d ",c[i]);
			i--;
		}
		printf("\n");
	}
	return 0;
}
#endif