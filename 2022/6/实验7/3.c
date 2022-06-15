#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *List;

void turn(List L);
void destroy(List L);

int main()
{
    int t;
    List A = (List)malloc(sizeof(Node));
    A->data = 0;
    A->next = NULL;
    Node *p = A;
    printf("请输入一个由整数组成的链表：\n");
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
    turn(A);
    Node *T = A;
    printf("逆置后的链表为：\n");
    for (int i = 0; i < A->data; i++)
    {
        T = T->next;
        printf("%d", T->data);
        if (i != A->data - 1)
            printf(" ");
        else
            printf("\n");
    }
    destroy(A);
    return 0;
}

void turn(List L)
{
    Node *address[L->data];
    Node *T = L;
    for (int i = 0; i < L->data; i++)
    {
        T = T->next;
        address[i] = T;
    }
    for (int i = 0; i < L->data; i++)
    {
        if (i == 0)
            address[i]->next = NULL;
        else
            address[i]->next = address[i - 1];
    }
    L->next = address[L->data-1];
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