//不习惯用函数


//不会调别的文件的函数
#include<stdio.h>
int main(void)
{int i,j,k,z,a,n;
	printf("首先祝这个电脑前的小可爱圣诞快乐(～￣▽￣)～");printf("\n");
	printf("接下来有几个选项需要您的选择你需要我的创造者给您画的圣诞树还是自己做一个呢？",n);
	printf("\n");
	printf("看创造者的选0如果想自己做呢选1祝您开心o(*^＠^*)o");printf("\n");
	scanf("%d",&a);
	if(a==0)
	{
char  p='_',q='|';
	for(i=1;i<=4;i++)
	{
		for(j=1;j<=46-i;j++)
			printf("%c",' ');
		putchar(47);
		if(i!=1){
		for(j=1;j<=2*(i-1);j++)
			printf("%c",' ');
		putchar(92);}
		else
			putchar(92);
		printf("\n");
	}
for(j=1;j<=46-i;j++)
			printf("%c",' ');
		putchar(47);
		putchar(p);putchar(p);
		printf("%c",' ');printf("%c",' ');printf("%c",' ');printf("%c",' ');
		putchar(p);putchar(p);
		putchar(92);
printf("\n");
for(i=1;i<=5;i++){
	for(j=1;j<=43-i;j++)
			printf("%c",' ');printf("%c",' ');
		putchar(47);
		for(j=1;j<=2*(i+1);j++)
printf("%c",' ');
		putchar(92);
printf("\n");

}
for(j=1;j<=44-i;j++)
			printf("%c",' ');
		putchar(47);
		putchar(p);putchar(p);putchar(p);putchar(p);putchar(p);
printf("%c",' ');printf("%c",' ');printf("%c",' ');printf("%c",' ');
		putchar(p);putchar(p);putchar(p);	putchar(p);putchar(p);
		putchar(92);
printf("\n");
for(i=1;i<=7;i++){
	for(j=1;j<=43-i;j++)
			printf("%c",' ');printf("%c",' ');
		putchar(47);
		for(j=1;j<=2*(i+1);j++)
printf("%c",' ');
		putchar(92);
printf("\n");
}
for(j=1;j<=44-i;j++)
			printf("%c",' ');
		putchar(47);
		putchar(p);putchar(p);putchar(p);
printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');printf("%c",' ');
		putchar(p);putchar(p);putchar(p);
		putchar(92);
printf("\n");
for(k=1;k<=2;k++){
	for(j=1;j<=48-i;j++)
			printf("%c",' ');
putchar(q);
printf("%c",' ');printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');
putchar(q);printf("\n");	}
for(j=1;j<=48-i;j++)
			printf("%c",' ');putchar(q);
printf("%c",' ');printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');
putchar(42);printf("%c",' ');printf("%c",' ');
printf("%c",' ');printf("%c",' ');putchar(q);
printf("\n");
for(j=1;j<=48-i;j++)
			printf("%c",' ');putchar(q);printf("%c",' ');
printf("%c",' ');printf("%c",' ');printf("%c",' ');
putchar(42);putchar(42);putchar(42);printf("%c",' ');
printf("%c",' ');printf("%c",' ');putchar(q);
printf("\n");
for(j=1;j<=48-i;j++)
			printf("%c",' ');putchar(q);printf("%c",' ');
printf("%c",' ');printf("%c",' ');
putchar(42);putchar(42);putchar(42);putchar(42);putchar(42);
printf("%c",' ');printf("%c",' ');putchar(q);
printf("\n");
for(j=1;j<=48-i;j++)
			printf("%c",' ');putchar(q);printf("%c",' ');printf("%c",' ');
putchar(42);putchar(42);putchar(42);putchar(42);putchar(42);
putchar(42);putchar(42);printf("%c",' ');putchar(q);
printf("\n");
for(k=1;k<=2;k++){
for(j=1;j<=48-i;j++)
			printf("%c",' ');putchar(q);
printf("%c",' ');printf("%c",' ');printf("%c",' ');printf("%c",' ');
putchar(42);putchar(42);putchar(42);printf("%c",' ');
printf("%c",' ');printf("%c",' ');putchar(q);
printf("\n");}
for(j=1;j<=120;j++)
putchar(35);
printf("\n");
}
	if(a==1)
	{
printf("请选择层数最多只有3层哦\(￣︶￣*\))");
printf("\n");
	scanf("%d",&z);
	if(z==1)
	{
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");

	}
	for(k=1;k<=2;k++)
	{
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
	}
	if(z==2){
for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");}
for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");}
	for(k=1;k<=2;k++){
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
for(k=1;k<=2;k++){
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
	}
if(z==3){
for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");}
for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");}
for(i=1;i<=3;i++)
	{
		for(j=1;j<=5-i;j++)
			printf("%c",' ');
		for(j=1;j<=2*i-1;j++)
			printf("%c",'*');
		printf("\n");
}
	for(k=1;k<=2;k++){
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
for(k=1;k<=2;k++){
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
for(k=1;k<=2;k++){
for(j=1;j<=3;j++)
			printf("%c",' ');putchar(42);putchar(42);putchar(42);printf("\n");
	}
}

	}

return 0;
}
