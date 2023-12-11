#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct information
{
    char name[50];
    int id;
    int Chinese;
    int Math;
    int English;
} information;

int MAX_NUM = 100;

//排序函数
int cmp(const void*a,const void* b);
//学生信息初始化函数
void information_init(information *students);

//学生信息录入函数
void information_input(information *students, int *num);

//学生信息排序函数
void information_sort(information *students, int *num);

//学生信息查询函数
void information_output(information *students, int *num);

//计算平均值函数
void average(information *students, int *num);

int main(void)
{
    int flag = -1;
    int num = 0;
    information students[MAX_NUM];
    information_init(students);
    printf("请您先输入一些学生的成绩:\n");
    information_input(students, &num);

    while (1)
    {
        printf("请选择您想进行的操作:\n1.学生成绩录入    2.学生成绩排序\n"
               "3.学生成绩查询    4.计算平均值\n"
               "5.退出程序\n输入操作前的序号即可:");
        scanf("%d", &flag);
        printf("\n");
        if (flag == 1)
            information_input(students, &num);
        else if (flag == 2)
            information_sort(students, &num);
        else if (flag == 3)
            information_output(students, &num);
        else if (flag == 4)
            average(students, &num);
        else if (flag == 5)
        {
            usleep(1000000);
            break;
        }
        else
        {
            printf("再给你一次机会\n");
            continue;
        }
    }
    return 0;
}

//学生信息初始化函数
void information_init(information *students)
{
    for (int i = 0; i < MAX_NUM; i++)
    {
        memset(students[i].name, 0, 50);
        students[i].id = 0;
        students[i].Chinese = 0;
        students[i].Math = 0;
        students[i].English = 0;
    }
}

//读入学生信息函数
void information_input(information *students, int *num)
{
    printf("您需要输入几名学++生的信息呢？(输入一个数字即可)\n");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d学生的信息:\n", i+1);
        printf("学号:");
        while (scanf("%d", &students[i + *num].id) == 0 || students[i + *num].id > 100000000 || students[i + *num].id < 1)
        {
            printf("十分抱歉,本程序的学号范围是1-100000000哦~,请您重新输入.");
            printf("学号:");
            continue;
        }
        printf("姓名:");
        while (scanf("%s", students[i + *num].name) == 0)
            continue;
        printf("语文:");
        while (scanf("%d", &students[i + *num].Chinese) == 0 || students[i + *num].Chinese > 100 || students[i + *num].Chinese < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("语文:");
            continue;
        }
        printf("数学:");
        while (scanf("%d", &students[i + *num].Math) == 0 || students[i + *num].Math > 100 || students[i + *num].Math < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("数学:");
            continue;
        }
        printf("英语:");
        while (scanf("%d", &students[i + *num].English) == 0 || students[i + *num].English > 100 || students[i + *num].English < 0)
        {
            printf("十分抱歉,本程序的课程分数范围是0-100哦~,请您重新输入成绩.\n");
            printf("英语:");
            continue;
        }
        printf("\n");
    }
    *num += n;
}

//学生信息排序函数
void information_sort(information *students, int *num)
{
    qsort(students,*num,sizeof(information),cmp);
    printf("已按照三门课程的平均成绩对学生进行排序\n\n");
}

//学生信息查询函数
void information_output(information *students, int *num)
{
    printf("已录入的学生信息如下:\n\n");
    for (int i = 0; i < *num; i++)
    {
        printf("第%i名学生:\n", i+1);
        printf("学号：%d\n", students[i].id);
        printf("姓名：%s\n", students[i].name);
        printf("语文：%d\n", students[i].Chinese);
        printf("数学：%d\n", students[i].Math);
        printf("英语：%d\n\n", students[i].English);
    }
    printf("已录入的学生信息展示完毕\n\n");
}

//计算平均值函数
void average(information *students, int *num)
{
    int sum[3] = {0,0,0};
    for(int i=0; i<*num; i++)
    {
        sum[0] += students[i].Chinese;
        sum[1] += students[i].Math;
        sum[2] += students[i].English;
    } 
    printf("已录入学生的语文平均成绩为:%.3lf\n",(double)sum[0]/3);
    printf("已录入学生的数学平均成绩为:%.3lf\n",(double)sum[1]/3);
    printf("已录入学生的英语平均成绩为:%.3lf\n\n",(double)sum[2]/3);
    printf("(以上平均成绩均保留三位有效数字)\n\n");
}

int cmp(const void*a,const void* b)
{
    information c = *(information*)a;
    information d = *(information*)b;
    int t = (d.Chinese + d.Math + d.English) - (c.Chinese + c.Math + c.English);
    if(t != 0)
        return t;
    else
        return c.id - d.id;
}