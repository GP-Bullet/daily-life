#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void input(char a[][20])
{
	int i;
	for(i=0;i<6;i++){
		scanf("%s",a[i]);
	}
}
int cmp(const void*a,const void*b)
{
    return strcmp((char*)a,(char*)b);
}
void sort(char a[][20])
{
    qsort(a,6,20,cmp);
}
void output(char a[][20])
{
	int i;
	for(i=0;i<6;i++){
		printf("%s\n",a[i]);
	}
}
int main()
{
	char a[6][20]={0};
	input(a);
	sort(a);
	output(a);

	return 0;
}