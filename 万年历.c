
#include<stdio.h>
int runnian(int year);
int distance(struct date d1);
int isdate(struct date d1);
void day(struct date d1);


#ifndef _DATE_H_
#define _DATE_H_

#define MONTH 12
#define WEEK 7

int month[2][MONTH] = { { 31,28,31,30,31,30,31,31,30,31,30,31 },   //平年每个月的天数
							{ 31,29,31,30,31,30,31,31,30,31,30,31 } }; //闰年每个月的天数
char *week[WEEK] = { (char*)"日",(char*)"一",(char*)"二",(char*)"三",(char*)"四",(char*)"五",(char*)"六" };

typedef struct _date {
	int date[6][WEEK];
}Dates;

void SeekMonth(void);
void SeekYear(void);
void SeekDay(void);

void Seekyear(void);
void Seekday(void);
void Seekmonth(void);

void Produce(int w, Dates * Date, int datenmuber);
void PrintMonth(char*week[], Dates * Date, int month);
void Print(char*week[], Dates * Date1, Dates * Date2, Dates * Date3, int month);

void Judge(Dates * Date, int i);
void Month(int count, int *m);
int IsLeapYear(int y);

#endif


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

int Calculation(struct date d1){
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
	return sum%7;
}


/*功能：根据1日所在星期，生成这个月的日期,并存于数组
参数： w 1日所在星期 datenmuber 一个月的天数*/
void Produce(int w, Dates * Date, int datenmuber)
{
	int d = 1;
	int i;
	for (i = 0; i < 6; i++)
	{
		int j;
		for (j = 0; j < 7; j++)
		{
			if ((i == 0 && j >= w) || (i > 0 && j >= 0)) {
				Date->date[i][j] = d;
				d++;
			}
			if (Date->date[i][j] >= datenmuber) {
				break;
			}
		}
		if (Date->date[i][j] >= datenmuber) {
			break;
		}
	}
}


void Print(char*week[], Dates * Date1, Dates * Date2, Dates * Date3, int month)
{
	/*打印月“1月”，“2月”......*/
	printf("\t");
	int i;
	for (i = 0; i < 3; i++)
	{
		printf(" %d月                 \t", month++);
	}
	printf("\n");

	/*打印星期 "日","一","二","三","四","五","六"*/
	printf("\t");
	for (i = 0; i < 3; i++)
	{

		int j;
		for (j = 0; j < 7; j++)
		{
			printf(" %s", week[j]);
		}
		printf("\t");
	}
	printf("\n");

	/* 打印日
		  1  2  3  4  5  6  7              1  2  3  4                       1
		  8  9 10 11 12 13 14     5  6  7  8  9 10 11     2  3  4  5  6  7  8
		 15 16 17 18 19 20 21    12 13 14 15 16 17 18     9 10 11 12 13 14 15
		 22 23 24 25 26 27 28    19 20 21 22 23 24 25    16 17 18 19 20 21 22
		 29 30 31                26 27 28 29 30 31       23 24 25 26 27 28 29
														 30*/
	for (i = 0; i < 6; i++)
	{
		printf("\t");

		Judge(Date1, i);
		Judge(Date2, i);
		Judge(Date3, i);
		printf("\n");
	}
}

void PrintMonth(char*week[], Dates * Date, int month)
{
	printf("\n\n");
	int i;
	printf("     ");
	printf("  %d月\n", month);

	printf("      ");
	for (i = 0; i < 7; i++)
	{
		printf(" %s", week[i]);
	}
	printf("\n");

	for (i = 0; i < 6; i++)
	{
		printf("      ");
		Judge(Date, i);
		printf("\n");
	}
}

void Judge(Dates * Date, int i)
{
	int j;
	for (j = 0; j < WEEK; j++)
	{
		if (Date->date[i][j] == 0) {
			printf("   ");
		}
		else {
			printf("%3d", Date->date[i][j]);
		}
	}
	printf("\t");
}
void Seekyear(void)
{
	int y = 0, c = 0, m = 0;  //w 星期， y 年， c 世 - 1，m 月
	int w1, w2, w3;
	int result = 0, year;

	printf("请输入要查询的年份：");
	scanf("%d", &y);

	year = y;
	result = runnian(y);

	c = y / 100;//年数的前两位
	y = y % 100;//年数的后两位

	int i, count = 0;


	printf("\n\t ===========================%d年Calendar===========================\n\n", year);

	/*以 3 x 4 的格式打印日历*/
	for (i = 0; i < 4; i++)
	{
		Dates Date1 = { 0 }, Date2 = { 0 }, Date3 = { 0 };//Date1，Date2, Date3存放横排每个月的日期

		Month(count, &m);
		w1 = Calculation();
		Produce(w1, &Date1, month[result][count++]);

		Month(count, &m);
		w2 = Calculation();
		Produce(w2, &Date2, month[result][count++]);

		Month(count, &m);
		w3 = Calculation();
		Produce(w3, &Date3, month[result][count++]);

		Print(week, &Date1, &Date2, &Date3, count - 2);
	}
	system("pause");
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
