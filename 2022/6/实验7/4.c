#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

typedef struct Node
{
    char name[50];
    int id;
    int Chinese;
    int Math;
    int English;
    struct Node *next;
} Node, *List;

int MAX_NUM = 100;

//链表初始化函数
List List_init();

//节点插入函数
void Node_insert(List L);

//学生信息排序函数
void List_sort(List L);

//学生信息查询函数
void List_output(List L);

//计算平均值函数
void average(List L);

//单链表删除函数
void destroy(List L);
int main(void)
{
    int flag = -1;
    List A = List_init();
    printf("提示：目前系统中还没有学生信息.\n\n");
    while (1)
    {
        printf("请选择您想进行的操作:\n1.学生成绩录入    2.学生成绩排序\n"
               "3.学生成绩查询    4.计算平均值\n"
               "5.退出程序\n输入操作前的序号即可:");
        scanf("%d", &flag);
        printf("\n");
        if (flag == 1)
            Node_insert(A);
        else if (flag == 2)
            List_sort(A);
        else if (flag == 3)
            List_output(A);
        else if (flag == 4)
            average(A);
        else if (flag == 5)
        {
            printf("再见.\n");
            break;
        }
        else
        {
            printf("输入有误,请输入序号1、2、3、4、5\n");
            continue;
        }
    }
    destroy(A);
    return 0;
}

//链表初始化函数
List List_init()
{
    List L = (List)malloc(sizeof(Node));
    L->id = 0;
    L->next = NULL;
    return L;
}

//节点插入函数
void Node_insert(List L)
{
    printf("希望录入的学生信息数量为：\n");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        Node *T = (Node *)malloc(sizeof(Node));

        Node *p = L;
        while (p->next)
            p = p->next;

        printf("请输入第%d学生的信息:\n", i + 1);
        printf("学号:");
        while (!scanf("%d", &T->id) || T->id > 100000000 || T->id < 1)
        {
            printf("学号范围是1-100000000,请重新输入.");
            printf("学号:");
            continue;
        }
        printf("姓名:");
        while (!scanf("%s", T->name))
            continue;
        printf("语文:");
        while (!scanf("%d", &T->Chinese) || T->Chinese > 100 || T->Chinese < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("语文:");
            continue;
        }
        printf("数学:");
        while (!scanf("%d", &T->Math) || T->Math > 100 || T->Math < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("数学:");
            continue;
        }
        printf("英语:");
        while (!scanf("%d", &T->English) || T->English > 100 || T->English < 0)
        {
            printf("课程分数范围是0-100,请重新输入成绩.\n");
            printf("英语:");
            continue;
        }
        printf("\n");
        p->next = T;
        T->next = NULL;
        p = T;
    }
    L->id += n;
}

//学生信息排序函数
void List_sort(List L)
{
    Node *a, *b, temp;
    if (L->next == NULL)
    {
        printf("当前没用学生信息,请先输入一些学生信息.\n\n");
        return;
    }
    if (L->next->next == NULL)
    {
        printf("当前只有一个学生信息,无需排序.\n\n");
        return;
    }
    a = L->next;
    while (a->next)
    {
        b = a->next;
        while (b)
        {
            if ((a->Chinese + a->Math + a->English) < (b->Chinese + b->Math + b->English))
            {
                temp = *a;
                *a = *b;
                *b = temp;
                temp.next = a->next;
                a->next = b->next;
                b->next = temp.next;
            }
            b = b->next;
        }
        a = a->next;
    }
    printf("已按照三门课程的平均成绩对学生进行排序\n\n");
}

//学生信息查询函数
void List_output(List L)
{
    printf("已录入的学生信息如下:\n\n");
    Node *p = L;
    int i = 1;
    while (p->next)
    {
        p = p->next;
        printf("第%i名学生:\n", i);
        printf("学号：%d\n", p->id);
        printf("姓名：%s\n", p->name);
        printf("语文：%d\n", p->Chinese);
        printf("数学：%d\n", p->Math);
        printf("英语：%d\n\n", p->English);
        i++;
    }
    printf("已录入的学生信息展示完毕\n\n");
}

//计算平均值函数
void average(List L)
{
    int sum[3] = {0, 0, 0};
    Node *p = L;
    while (p->next)
    {
        p = p->next;
        sum[0] += p->Chinese;
        sum[1] += p->Math;
        sum[2] += p->English;
    }
    printf("已录入学生的语文平均成绩为:%.3lf\n", (double)sum[0] / L->id);
    printf("已录入学生的数学平均成绩为:%.3lf\n", (double)sum[1] / L->id);
    printf("已录入学生的英语平均成绩为:%.3lf\n\n", (double)sum[2] / L->id);
    printf("(以上平均成绩均保留三位有效数字)\n\n");
}
void destroy(List L)
{
    Node *p = L;
    Node *T;
    while (p)
    {
        T = p->next;
        free(p);
        p = T;
    }
}