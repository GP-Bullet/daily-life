#include<stdio.h>
#include <stdio.h>
#include <malloc.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;


int getLen(LinkList H);
LinkList creat_List();
void output(LinkList H);
LinkList combine_list(LinkList A, LinkList B);
void destroy(LinkList list);

int main()
{   int m,n;        
    LinkList A, B, C;
    A = creat_List();
    B = creat_List();
    m=getLen(A);
    n=getLen(B);
    if(n>=m){
        C = combine_list(A, B);
    }else{
        C = combine_list(B, A);
    }
    
    output(C);
    destroy(C);
    return 0;
}
int getLen(LinkList H)
{
    LinkList pr = H->next;
	int count = 0;
	
	while(pr != NULL)
	{
		pr = pr->next;
		count++; 
	}

	return count;
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
    do
    {   
        scanf("%d", &x);
        LinkList p;
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->next = NULL;
        p->data = x;

        q->next = p;
        q = p;
    }while(getchar()!='\n');
    return H;
}

// LinkList combine_list(LinkList A, LinkList B)
// {
//     LinkList C,p,q,a,b;
//     C=A;
//     p=A;
//     q=B;    
//     while(q->next!=NULL){
//         a=p->next;
//         b=q->next;
//         p->next=q;
//         p=a;
//         q->next=p;
//         q=b;
//     }
//     return C;
// }


LinkList combine_list(LinkList A, LinkList B)
{   
    LinkList C;
    LinkList pa, pb, qa, qb;
    pa = A->next;  
    pb = B->next;
    C = A;        
    while(pa && pb)
    {
        qa = pa;
        qb = pb;
        pa = pa->next;
        pb = pb->next;
        qb->next = qa->next;
        qa->next = qb;
    }
    if(!pa)  // 如果 A 链表的长度小于 B 链表的长度
        qb->next = pb; // 将 B 的后续节点连接到新链表的尾端
    pb = B;  // 准备删除 B 链表
    free(pb);

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