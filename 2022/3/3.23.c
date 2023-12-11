#include<stdio.h>
#include<stdlib.h>
#include"Calendar.h"

int main()
{
	int n = 1;
//	system("mode con cols=35 lines=25");                                //设置窗口大小
//	system("color 5f");
	while (n)
	{
		printf("\n");
		printf(" ╔══════════════════════════════╗\n");
		printf(" ║----------- 万年历 ------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║-----------年历查询----------1║\n");
		printf(" ║-----------月历查询----------2║\n");
		printf(" ║-----------日历查询----------3║\n");
		printf(" ║---------- 按0退出! ---------0║\n");
		printf(" ║------------------------------║\n");
		printf(" ╚══════════════════════════════╝\n\n");
		printf("请选择功能键：");
		scanf("%d", &n);
		if (n > 3 || n < 0) {
			printf("  输入错误！\n");
		}
		else {
			switch (n)
			{
			case 0: printf("\n 返回主界面\n");
				n = 0;
				break;
			case 1: SeekYear();
				break;
			case 2: SeekMonth();
				break;
			case 3: SeekDay();
				break;
			}
		}
//		system("CLS");
	}
	return 0;
}


void SeekYear(void)
{
	int n = 1;
	while (n)
	{
//		system("CLS");
//		system("mode con cols=35 lines=25");                                //设置窗口大小
//		system("color 5f");
		printf(" ║------------------------------║\n");
		printf(" ║-----欢迎使用年历查询系统-----║\n");
		printf(" ║-----可供查询的年历 ----------║\n");
		printf(" ║--------- 按1查询！-----------║\n");
		printf(" ║--------- 按0退出! -----------║\n");
		printf(" ╚══════════════════════════════╝\n\n");
		printf("请选择功能键：");
		scanf("%d", &n);

		if (n > 1 || n < 0) {
			printf("输入错误");
		}
		else {
			switch (n)
			{
			case 0: printf("\n 返回主界面\n");
				n = 0;
				break;
			case 1: Seekyear();
				break;
			}
		}
	}
}

void Seekyear(void)
{
	int y = 0, c = 0, m = 0;  //w 星期， y 年， c 世 - 1，m 月
	int w1, w2, w3;
	int result = 0, year;

	printf("请输入要查询的年份：");
	scanf("%d", &y);

	year = y;
	result = IsLeapYear(y);

	c = y / 100;//年数的前两位
	y = y % 100;//年数的后两位

	int i, count = 0;


	printf("\n\t ===========================%d年Calendar===========================\n\n", year);

	/*以 3 x 4 的格式打印日历*/
	for (i = 0; i < 4; i++)
	{
		Dates Date1 = { 0 }, Date2 = { 0 }, Date3 = { 0 };//Date1，Date2, Date3存放横排每个月的日期

		Month(count, &m);
		w1 = Calculation((count < 2 ? y - 1 : y), c, m);
		Produce(w1, &Date1, month[result][count++]);

		Month(count, &m);
		w2 = Calculation((count < 2 ? y - 1 : y), c, m);
		Produce(w2, &Date2, month[result][count++]);

		Month(count, &m);
		w3 = Calculation((count < 2 ? y - 1 : y), c, m);
		Produce(w3, &Date3, month[result][count++]);

		Print(week, &Date1, &Date2, &Date3, count - 2);
	}
//	system("pause");
}

void SeekMonth(void)
{
	int n = 1;
	while (n)
	{
//		system("CLS");

		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------欢迎使用月历查询系统----║\n");
		printf(" ║------可供查询的月历----------║\n");
		printf(" ║------1月——12月-------------║\n");
		printf(" ║---------- 按1查询! ----------║\n");
		printf(" ║---------- 按0退出! ----------║\n");
		printf(" ╚══════════════════════════════╝\n\n");
		printf("请选择功能键：");
		scanf("%d", &n);
		if (n > 1 || n < 0) {
			printf("输入错误");
		}
		else {
			switch (n)
			{
			case 0: printf("\n 返回主界面\n");
				n = 0;
				break;
			case 1: Seekmonth();
				break;
			}
		}
	}
}

void Seekmonth(void)
{
	int y = 0, c = 0, m = 0;  //w 星期， y 年， c 世 - 1，m 月
	int w1;
	int result = 0, year;
	int count = 0;

	printf("请输入要查询的年份和月份：(格式如：2019 2)\n");
	scanf("%d %d", &y, &count);

	year = y;
	result = IsLeapYear(y);

	c = y / 100;//年数的前两位
	y = y % 100;//年数的后两位

	Dates Date = { 0 };//Date1，Date2, Date3存放横排每个月的日期

	Month(count, &m);
	w1 = Calculation((count < 2 ? y - 1 : y), c, m);
	Produce(w1, &Date, month[result][count - 1]);

	system("CLS");
	printf("\n\n--------------%d 年--------------\n", year);
	PrintMonth(week, &Date, count);
	printf("\n");
//	system("pause");
}

void SeekDay(void)
{
	int n = 1;
	while (n)
	{
//		system("CLS");

		printf(" ║------------------------------║\n");
		printf(" ║------------------------------║\n");
		printf(" ║------欢迎使用日历查询系统----║\n");
		printf(" ║------可供查询的日历----------║\n");
		printf(" ║------1日——28/29/30/31日----║\n");
		printf(" ║----------按1查询! -----------║\n");
		printf(" ║----------按0退出!------------║\n");
		printf(" ╚══════════════════════════════╝\n\n");
		printf("请选择功能键：");
		scanf("%d", &n);
		if (n > 1 || n < 0) {
			printf("输入错误");
		}
		else {
			switch (n)
			{
			case 0: printf("\n 返回主界面\n");
				n = 0;
				break;
			case 1: Seekday();
				break;
			}
		}
	}
}

void Seekday(void)
{
	int y = 0, c = 0, m = 0, d = 0;  //w 星期， y 年， c 世 - 1，m 月
	int w1;
	int result = 0, year;
	int count = 0;

	printf("请输入要查询的年份和月份以及日：(格式如：2019 2 1)\n");
	scanf("%d %d %d", &y, &count, &d);

	year = y;
	result = IsLeapYear(y);

	c = y / 100;//年数的前两位
	y = y % 100;//年数的后两位

	Month(count, &m);
	y = count < 2 ? y - 1 : y;

	w1 = y + (y / 4) + (c / 4) - 2 * c + (26 * (m + 1) / 10) + d - 1;
	if (w1 < 0) {
		w1 = w1 - (w1 / 7 - 1) * 7;
	}
	else {
		w1 = w1 % 7;
	}
	printf("\n");
	printf("%d年%d月%d日：", year, count, d);
	switch (w1)
	{
	case 0: printf("星期日"); break;
	case 1: printf("星期一"); break;
	case 2: printf("星期二"); break;
	case 3: printf("星期三"); break;
	case 4: printf("星期四"); break;
	case 5: printf("星期五"); break;
	case 6: printf("星期六"); break;
	}
	printf("\n");
//	system("pause");
}


/*功能：判断是不是闰年
参数：y 年
返回值：0 平年， 1 闰年*/
int IsLeapYear(int y)
{
	int flag = 0;
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		flag = 1;
	}
	return flag;
}

void Month(int count, int *m)
{
	if (count < 2) {
		*m = count + 13;
	}
	else {
		*m = count + 1;
	}
}

/*功能：计算某年某月某日是星期几
参数：y 年（后两位）   c 世纪 - 1   m 月
返回值： w 星期*/
int Calculation(int y, int c, int m)
{
	int d = 1;
	int w;
	w = y + (y / 4) + (c / 4) - 2 * c + (26 * (m + 1) / 10) + d - 1;
	if (w < 0) {
		w = w - (w / 7 - 1) * 7;
	}
	else {
		w = w % 7;
	}
	return w;
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