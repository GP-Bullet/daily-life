//?变长数组?


//若不支持变长数组
//只能变行
//!p++
#include<stdio.h>
#define N 3
void copy_arr(double* p1, double* p2, int n);
void pr(int,double *p);
int main(void)
{
	int i,j;
	double a[N][5] = { 
    {1.1,4.4,5.5,3.3,2.2},
    {6.6,7.7,1.1,2.2,3.3},
    {4.4,5.5,6.6,7.7,8.8} };
	double b[N][5];
	for(i=0;i<N;i++)
	copy_arr(b[i],a[i], 5);
	printf("a数组：\n");
	pr(N,a[0]);
	printf("b数组：\n");
	pr(N, b[0]);
    
	return 0;
}
void copy_arr(double* p1, double* p2, int n)
{
	int num;
	for (num = 0;num < n;num++, p1++, p2++)
		*p1 = *p2;
}
void pr(int m, double *p)
{
	int i, j;
	for (i = 0;i < m;i++,p++)
	{
		for (j = 0;j < 5;j++,p++)
			printf("%lf ",*p);
			p--;
		printf("\n");
	}
}




//使用变长数组，编译器不支持
/*
#include<stdio.h>
#define rows  3
#define cols  5
void print(int m,int n,double*p);
void copy(double *p1,double *p2,int m,int n);

int  main(){
	double source[rows][cols] = {
    {1.2,2,3.6,4,5.5},
    {2,2.7,3.8,5.3,10},
    {1.1,6,4,6.5,5.3}
    };
    double target[rows][cols];
	copy(source[0][0],target[0][0],rows,cols);
	print(rows,cols,source[0][0]);
	printf("\n");
	print(rows,cols,target[0][0]);

	return  0;
}

void copy(double *p1,double *p2,int m,int n){
	int i,j;
	for(i=0;i<m;i++,p1++,p2++){
		for(j=0;j<n;j++,p1++,p2++)
			*p2=*p1;
			p1--;
			p2--
	}
	
}
void print(int m,int n,double*p){
	int i,j;
	for(i=0;i<m,i++,p++){
		for(j=0;j<n;j++,p++){
			printf("%.1lf",*p);
			p--;
		}
	}
}
*/
