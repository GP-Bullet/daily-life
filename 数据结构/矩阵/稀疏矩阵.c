#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct {
	int i,j;//行，列
	int data;
} matrix;

int main() {
	matrix a[MAX];
	matrix b[MAX];
	matrix c[MAX];
	int row;
	int col;
	int n1,n2,n3;
	int k,t;
	scanf("%d %d",&row,&col);
	scanf("%d",&n1);
	int arr1[n1][3];
	for(k=0; k<n1; k++) {
		for(t=0; t<3; t++) {
			scanf("%d",&arr1[k][t]);
			if(t==0) {
				a[k].i=arr1[k][t];
			}
			if(t==1) {
				a[k].j=arr1[k][t];
			}
			if(t==2) {
				a[k].data=arr1[k][t];
			}
		}
	}//输入矩阵a的非零元素位置及数值,并将其存入结构体中

	scanf("%d",&n2);
	int arr2[n2][3];
	for(k=0; k<n2; k++) {
		for(t=0; t<3; t++) {
			scanf("%d",&arr2[k][t]);
			if(t==0) {
				b[k].i=arr2[k][t];
			}
			if(t==1) {
				b[k].j=arr2[k][t];
			}
			if(t==2) {
				b[k].data=arr2[k][t];
			}
		}
	}//输入矩阵b的非零元素位置及数值，并将其存入结构体中

	//两矩阵元素相加
	int m=0,n=0;
	t=0;
	int temp;
	while(m<n1&&n<n2) {
		if(a[m].i==b[n].i) {
			if(a[m].j==b[n].j) {
				temp=a[m].data+b[m].data;
				if(temp!=0) {
					c[t].i=a[m].i;
					c[t].j=a[m].j;
					c[t].data=temp;
					t++;
				}
				m++;n++;
				continue;
			}
			if(a[m].j<b[n].j) {
				c[t].i=a[m].i;
				c[t].j=a[m].j;
				c[t].data=a[m].data;
				t++;
				m++;
				continue;
			}
			if(a[m].j>b[n].j) {
				c[t].i=b[n].i;
				c[t].j=b[n].j;
				c[t].data=b[n].data;
				t++;
				n++;
				continue;
			}
		}
		if(a[m].i<b[n].i) {
			c[t].i=a[m].i;
			c[t].j=a[m].j;
			c[t].data=a[m].data;
			t++;
			m++;
			continue;
		}
		if(a[m].i>b[n].i) {
			c[t].i=b[n].i;
			c[t].j=b[n].j;
			c[t].data=b[n].data;
			t++;
			n++;
			continue;
		}
	}

	int p;
	//a矩阵还有非零元素
	if(m<n1) {
		for(p=m; p<n1; p++) {
			c[t].i=a[p].i;
			c[t].j=a[p].j;
			c[t].data=a[p].data;
			t++;
		}
	}

	//b矩阵还有非零元素
	if(n<n2) {
		for(p=n; p<n2; p++) {
			c[t].i=b[p].i;
			c[t].j=b[p].j;
			c[t].data=b[p].data;
			t++;
		}
	}

	int q;
	printf("%d\n",t);
	for(q=0; q<t; q++) {
		if(c[q].data>0.1) {
			printf("%d %d %d\n",c[q].i,c[q].j,c[q].data);
		}
	}
	return 0;
}
