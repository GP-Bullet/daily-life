#include<stdio.h>
#include<stdlib.h>
//综合题

//如果不分配内存会怎样

#define LEN sizeof(struct friend)
struct friend{
    int num;
    struct friend *next;
};

struct friend *head,*tail;

void create(int n)
{   
    int i;
    struct friend *p,*q;
    p=(struct friend*)malloc(LEN);
    p->num=1;
    p->next=NULL;
    head=p;
    q=p;
    


    for(i=2;i<=n;i++){
        p=(struct friend*)malloc(LEN);
        p->num=i;
        q->next=p;
        q=p;//q结点指向链表尾部结点
        p->next=NULL;
    }
    //这里用p可以吗
    tail=q;
    tail->next=head;
}

void delete(int m){
    int flag=0;
    struct friend *q,*p;
    q=tail;
    do{
        p=q->next;
        flag++;
        if(flag%m==0){
            printf("%d号小盆友退出了\n",q->next->num);
            q->next=p->next;
            free(p);
        }else{
            q=p;
        }
    }while(q!=q->next);
    head=q;
    
    printf("%d号小盆友退出了\n",head->num);
    free(head);
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    create(n);

    delete(m);
    
    return 0;
}