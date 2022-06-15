#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
} Node, *List;

List creat_List();
void output(List H);
List combine_list(List A, List B);
void destroy(List list);

int main()
{
    List A, B, C;
    printf("请输入一个非递增有序数列：\n");
    A = creat_List();
    printf("请输入一个非递减有序数列：\n");
    B = creat_List();

    C = combine_list(A, B);
    printf("归并后的非递减有序数列为：\n");
    output(C);
    destroy(C);
    return 0;
}

void output(List L)
{
    Node *p;
    p = L;
    if (L->next != L)
    {
        while (p->next != L)
        {
            p = p->next;
            printf("%d", p->data);
            if (p->next != NULL)
                printf(" ");
        }
        printf("\n");
    }
    else
        printf("这是一个空链表\n");
}
List creat_List()
{
    //尾插法
    List L;
    Node *q;
    L = (Node *)malloc(sizeof(Node));
    L->prev = L;
    L->next = L;

    int x;
    q = L;
    do
    {
        scanf("%d", &x);
        Node *T;
        T = (Node *)malloc(sizeof(Node));
        T->prev = NULL;
        T->next = NULL;
        T->data = x;

        q->next = T;
        T->prev = q;
        T->next = L;
        L->prev = T;
        q = T;
        L->data++;
    } while (getchar() != '\n');
    return L;
}

List combine_list(List A, List B)
{
    List C = (List)malloc(sizeof(Node));
    C->data = 0;
    C->prev = C;
    C->next = C;

    Node *pa, *pb, *qa, *qb, *pc = C;
    pa = A->prev;
    pb = B->next;
    while (pa != A || pb != B)
    {
        if (pa != A && pa->data <= pb->data)
        {
            qa = pa;
            pa = pa->prev;
            pc->next = qa;
            C->prev = qa;
            qa->prev = pc;
            qa->next = C;
            pc = pc->next;
            C->data++;
        }
        else
        {
            qb = pb;
            pb = pb->next;
            pc->next = qb;
            C->prev = qb;
            qb->prev = pc;
            qb->next = C;
            pc = pc->next;
            C->data++;
        }
    }

    free(A);
    free(B);
    return C;
}

void destroy(List L)
{
    Node *p = L;
    Node *T;
    while (p != L)
    {
        T = p->next;
        free(p);
        p = NULL;
        p = T;
    }
}