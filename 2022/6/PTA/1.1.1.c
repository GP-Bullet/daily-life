#include <stdio.h>
#include <malloc.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;

LinkList creat_List();
void output(LinkList H);
LinkList combine_list(LinkList A, LinkList B);
void destroy(LinkList list);

int main()
{
    LinkList A, B, C;
    A = creat_List();
    B = creat_List();

    C = combine_list(A, B);

    output(C);

    free(A);
    free(B);
    destroy(C);
    return 0;
}
void output(LinkList H)
{
    if (H->next)
    {
        LinkList p;
        p = H->next;
        while (p)
        {
            printf("%d", p->data);
            if (p->next != NULL)
                printf(" ");
            p = p->next;
        }
        printf("\n");
    }
    else
        printf("NULL");
}
LinkList creat_List()
{
    //尾插法
    LinkList H, q;
    int x;
    H = (LinkNode *)malloc(sizeof(LinkNode));
    H->next = NULL;
    q = H;
    while (scanf("%d", &x) && x != -1)
    {
        LinkList p;
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->next = NULL;
        p->data = x;

        q->next = p;
        q = p;
    }
    return H;
}
LinkList combine_list(LinkList A, LinkList B)
{
    //归并排序
    LinkList C, p;
    C = (LinkNode *)malloc(sizeof(LinkNode));
    C->next = NULL;
    p = C;
    A = A->next;
    B = B->next;
    while (A && B)
    {
        if (A->data > B->data)
        {
            p->next = B;
            B = B->next;
            p = p->next;
        }
        else
        {
            p->next = A;
            A = A->next;
            p = p->next;
        }
    }
    if (A)
    {
        p->next = A;
    }
    if (B)
    {
        p->next = B;
    }
    return C;
}

void destroy(LinkList list)
{
    LinkNode *cur ,*ret;
    ret = list;
    while (ret)
    {
        cur = ret->next;
        free(ret);
        ret = cur;
    }
}