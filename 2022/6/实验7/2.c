#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *List;

void calculate(List L, int *max, int *min, double *average);
void destroy(List L);

int main()
{
    int t, max, min;
    double average;
    List A = (List)malloc(sizeof(Node));
    A->data = 0;
    A->next = NULL;
    Node *p = A;
    printf("请输入一批正整数：\n");
    do
    {
        scanf("%d", &t);
        Node *T = (Node *)malloc(sizeof(Node));
        T->data = t;
        T->next = NULL;
        p->next = T;
        p = p->next;
        A->data++;
    } while (getchar() != '\n');
    calculate(A, &max, &min, &average);
    printf("最大值为:%d,最小值为:%d,平均值为:%.3lf.\n", max, min, average);
    destroy(A);
    return 0;
}

void calculate(List L, int *max, int *min, double *average)
{
    *max = *min = L->next->data;
    *average = 0;
    double sum = 0;
    Node *T = L;
    for (int i = 0; i < L->data; i++)
    {
        T = T->next;
        sum += T->data;
        if (*max < T->data)
            *max = T->data;
        if (*min > T->data)
            *min = T->data;
    }
    *average = sum / L->data;
}
void destroy(List L)
{
    Node *T = L;
    Node *p;
    while (T)
    {
        p = T->next;
        free(T);
        T = p;
    }
}