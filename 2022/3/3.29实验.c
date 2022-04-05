//1
#if 0
#include<stdio.h>
int main(){
	float s=0;
	int n=1;
	while(s<=15){
		s+=1.0/n;
		n++;
	}
	printf("%f %d",s,n);
	return 0;
}
#endif

//2
#if 0
#include<stdio.h>

int main(){

    double  S=0;
	int a=1;
	
	for(int i=1;;i++){

		if(i%2){
			a=1;
		}else{
			a=-1;
		}

		double t=1;
		for(int n=1;n<=i;n++){
			t*=n;
		}
		if(1/t<=1e-6)break;
		S=S+a/t;
//		printf("%lf\n",a/t);
	}
	printf("%lf",S);
	return 0;
}
#endif



//3
#if 0
#include<stdio.h>
int sushu(int a){
	for(int i=2;i<=a/2.0;i++){
		if(a%i==0) return 0;
	}
	return 1;
}

int main(){
	int i;int j=0;
	for(i=100;i<=200;i++){
		if(sushu(i)&&sushu(i+2)){
			printf("%d %d\n",i,i+2);
		}
	}	
	return 0;
}

#endif


//4
#if 0
#include<stdio.h>
int main(){
	//注意sum每次都要清零
	//int sum=0;
	int sum;
	int a[100];
	int count=0;
	for(int i=1;i<=1000;i++){
		sum=0;
		for(int j=1;j<i;j++){
			if(i%j==0){
				sum=sum+j;
			}
		}
		if(sum==i){
			
			for(int j=1;j<i;j++){
				if(i%j==0){
					a[count++]=j;
				}
			}
			printf("%d its factors are ",i);
			for(int j=0;j<count;j++){
				printf("%d,",a[j]);
			}
			count=0;
			printf("\n");
		}
	}
	return 0;
}
#endif


//5
#if 0
#include<stdio.h>
int main(){
	int i;
	double sum=0.0002;
	for(i=1;;i++){
		sum*=2;
		if(sum>8848)break;
		printf("%lf\n",sum);
	}
	printf("%d\n",i);
}
#endif



//7
#if 0
#include<stdio.h>
int main(){
	int n;
	
	scanf("%d",&n);//输入最大宽度

	for(int i=1;i<=(n+1)/2;i++){
		for(int j=1;j<=(n+1)/2-i;j++){
			printf(" ");
		}
		if(i==1){
			printf("*\n");
			
		}else{
			printf("*");
			for(int k=1;k<=2*(i-1)-1;k++){
				printf("+");
			}
			printf("*");
			printf("\n");
		}	
	}
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<=i;j++){
			printf(" ");
		}
		if(i==n/2){
			printf("*\n");
		}else{
			printf("*");
			for(int k=1;k<=2*(n/2-i)-1;k++){
				printf("+");
			}
			printf("*");
			printf("\n");
		}
	}
	return 0;
}

#endif


//6
#if 0
//没有好的调试技巧
#include<stdio.h>
#define PI 3.1415926535//防止内存溢出,利用周期性

int main(){
	double x;
	scanf("%lf",&x);
	
	double sum=x;
	int a=-1;
	double t=1,t_x=x-2*PI*(int)(x/(2*PI));
	for(int i=1;;i=i+2){//注意是i=i+2不是i+2

		t=t*(i+1)*(i+2);
		t_x=t_x*x*x;	
		if((t_x/t)<1e-5)break;
		
		sum+=a*t_x/t;

		a*=-1;
	}
	printf("sin(%lf)=%lf",x,sum);
	return 0;
}
#endif



//8
#if 0
//没有读清楚题目
#include<stdio.h>
int main(){
	int a[40],n;
	for(int i=1;i<=36;i++){
		a[i]=i;
	}
	int c;
	for(c=0;c<=15;c++){
		int sum=a[1+c]+a[2+c]+a[4+c]+a[7+c]+a[11+c]+a[16+c]+a[22+c];
		if(sum==105){
			break;
		}
	}
	printf("%d %d %d %d %d %d %d\n",a[1+c],a[2+c],a[4+c],a[7+c],a[11+c],a[16+c],a[22+c]);
}
#endif



//9
#if 0
//i和j的双重循环使用aibj的组合
#include<stdio.h>
int main(){
	char a[4]={' ','A','B','C'};
	char b[4]={' ','X','Y','Z'};

	for(int i=1;i<=3;i++){
		
		for(int j=1;j<=3;j++){
			if(!(a[i]=='A'&&b[j]=='X'||a[i]=='C'&&(b[j]=='X'||b[j]=='Z')))
			printf("%c %c\n",a[i],b[j]);
		}

}


	return 0;
}

#endif



//10
#if 1

#include<stdio.h>
int runnian(int year);
int distance(struct date d1);
int isdate(struct date d1);
void day(struct date d1);


//用一个结构体更方便
struct date{
	int year;
	int mon;
	int day;
};


int runnian(int year){
	
	
	if(year%4==0&&year%100!=0||year%400==0){
		
		return 1;
	}else{
		
		return 0;
	}

}

int isdate(struct date d1){
		if(d1.mon>12){
			printf("该日期不合法\n");
			return 0;
		}else{
			if((d1.mon==1||d1.mon==3||d1.mon==5||d1.mon==7||d1.mon==8||d1.mon==10||d1.mon==12)&&d1.day<=31){
				printf("%d年%d月%d日合法\n",d1.year,d1.mon,d1.day);
				return 1;
			}else if((d1.mon==4||d1.mon==6||d1.mon==9||d1.mon==11)&&d1.day<=30){
				printf("%d年%d月%d日合法\n",d1.year,d1.mon,d1.day);
				return 1;
			}else{
				if(runnian(d1.year)){
					if(d1.mon==2&&d1.day<=29){
					printf("%d年%d月%d日合法\n",d1.year,d1.mon,d1.day);
					return 1;
					}else{
					printf("该日期不合法\n");
					return 0;
					}
				}else{
					if(d1.mon==2&&d1.day<=28){
						printf("%d年%d月%d日合法\n",d1.year,d1.mon,d1.day);
						return 1;
					}else{
						printf("该日期不合法\n");
						return 0;
					}
				}
			}			
		}
}
void day(struct date d1){
	//今年的某一天
	//2022.1.1六
	//计算距1.1  X天
	//(6+x)%7=

	int dis=distance(d1);//相距
	//int yuandan;
	//实现2001~2099年  算出各年1.1的是星期几
	//yuandan=((d1.year-2001)+(d1.year-2001)/4+1)%7;


	/*实现1000~9999年
	if(d1.year/1000!=0){
		yuandan=((d1.year-d1.year/1000*1000-1)+(d1.year-d1.year/1000*1000-1)/4+1)%7;
	}else if(d1.year/100!=0){  //100~999
		yuandan=((d1.year-d1.year/100*100-1)+(d1.year-d1.year/100*100-1)/4+1)%7;
	}else if(d1.year/10!=0){ //10~99
		yuandan=((d1.year-d1.year/10*10-1)+(d1.year-d1.year/10*10-1)/4+1)%7;
	}else{					//0~9
		yuandan=((d1.year-d1.year-1)+(d1.year-d1.year-1)/4+1)%7;
	}
	注意2035/1000*1000=2000*/
	
	//补充知识：公年1年1月1日是星期一

	
	switch(dis%7){
		case 0:
			printf("星期日\n");
			break;
		case 1:
			printf("星期一\n");
			break;
		case 2:
			printf("星期二\n");
			break;
		case 3:
			printf("星期三\n");
			break;
		case 4:
			printf("星期四\n");
			break;
		case 5:
			printf("星期五\n");
			break;
		case 6:
			printf("星期六\n");
			break;
	}	
}

int distance(struct date d1){
	long long sum=0;
	int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(runnian(d1.year)){
		month[2]=29;
	}
	//把年也算上从公元1年1月1日开始
	for(int i=1;i<d1.year;i++){
		if(runnian(i)){
			sum+=366;
		}else{
			sum+=365;
		}
	}
	for(int i=1;i<d1.mon;i++){
		sum+=month[i];
	}
		sum+=d1.day;
	return sum;
}


int main(){
	
	struct date d1;
	
	scanf("%d %d %d",&d1.year,&d1.mon,&d1.day);
	if(isdate(d1)){//是否合法
		
		if(runnian(d1.year)){//是不是闰年
			printf("该年为闰年\n");
		}else{
			printf("该年不是闰年\n");
		}
		day(d1);//任意日期判断星期几
	}
	return 0;
}
#endif