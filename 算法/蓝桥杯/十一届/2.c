#include<stdio.h>
int main()
{
	int i,j,k;
	double sum=0,t;
	double p=1;
	for(i=1;;i++,p=1)
	{
		if(i%2)
		{
			k=1;
		}
		else
		{
			k=-1;
		}	
		for(j=1;j<=i;j++)
		{
			p *= j;
		}
		t = k/p;
		if(1/p<=(1e-6))
		{
			break;
		}
		sum+=t;	
	}
	printf("%lf",sum);
	return 0;
}
