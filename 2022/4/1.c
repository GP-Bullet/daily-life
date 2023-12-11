#include<stdio.h> 
int main()
{
	int max,grade[10],sum=0;
	float average;
	printf("请输入成绩\n");
	for(int i=0;i<10;i++)
	{
		scanf("%d",&grade[i]);
	}
    for(int j=0;j<10;j++){
        printf("%d ",grade[j]);
    }
    max=grade[0];
	for(int i=0;i<10;i++)
	{
		if(max<grade[i])
		max=grade[i];
	}
	for(int i=0;i<10;i++)
	{
		sum=sum+grade[i];
		average=sum/10.0;
	} 
	printf("最大值为：%d\n  平均值为%f\n",max,average);
	
    return 0;
	
}