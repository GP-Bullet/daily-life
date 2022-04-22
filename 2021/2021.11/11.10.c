#include<stdio.h>
int main(){
	int a[100000];
	int i,j,k;
	for(i=0;i<100000;i++){
		a[i]=1;
	}
	int l,m,u,v;
	scanf("%d %d",&l,&m);
	
	for(k=0;k<m;k++){
		scanf("%d %d",&u,&v);
		for(j=u;j<=v;j++);{
			a[j]=0;
		}
	}
    int count=0;
for(k=0;k<=l;k++)
{
	if(a[i]==1)
	count++;
}
	printf("%d",count);

return 0;
}
