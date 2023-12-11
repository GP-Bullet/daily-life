#include<stdio.h>
#define M 3
#define N 4

int max,min;

void fun(int a[][N],int *b){

	int  i,j;
	for(i=0; i<N; i++) {
		b[i]=a[0][i];
		for(j=1; j<M; j++){
			if(b[i]< a[j][i])
				b[i]=a[j][i];
		}
            
	}
	
	min=b[0];
	max=b[0];
	for(int i=0;i<4;i++){
		if(b[i]>max)
            max=b[i];
        if(b[i]<min)
            min=b[i];
		
	}
}

int main()
{
	
	int a[M][N],b[N],i,j;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			scanf("%d",&a[i][j]);
		}
	}
	printf("The original data is:\n");
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf((j==N-1)?"%6d\n":"%6d",a[i][j]);//这里妙呀
		}
	}
	fun(a,b);

	printf("\nThe result is:\n");
	for(i=0;i<N;i++)
		printf("%4d",b[i]);
	printf("\nmax=%d,min=%d\n",max,min);

	return 0;
}