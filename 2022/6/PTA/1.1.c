#include<stdio.h>
#include<stdlib.h>
//两个有序链表序列的合并
struct li
{
    int num;
    struct li *next;
};

 
struct li* create()
{   
    struct li*head;
    struct li*p1,*p2;//p1新结点的指针,p2末尾指针
    int num;
    int tep=0;
    p1=p2=(struct li*)malloc(sizeof(struct li));
    head=p1;
    while(scanf("%d",&p1->num) && p1->num!=-1){
        p1=(struct li*)malloc(sizeof(struct li));
        p2->next=p1;
        p2=p1;
    }
    p2->next=NULL;
    free(p1);
    return head;
}
struct li* sort(struct li*A,struct li*B)
{
    struct li* head,*p;
    head=(struct li*)malloc(sizeof(struct li));
    head->next=NULL;
    head->next = NULL;
	p = head;
	A = A->next;
	B = B->next;
	while(A&&B){
		if(A->num > B->num){
			p->next = B;
			B = B->next;
			p = p->next;
		}
		else{
			p->next = A;
			A = A->next;
			p = p->next;
		}
	} 
	if(A){
		p->next = A;
	}
	if(B){
		p->next = B;
	}
	return head;


}

void print(struct li*C)
{
    struct li*p;
    p=C;
    while(p!=NULL){
        printf("%d ",p->num);
        p=C->next;
    }

}
int main(){
    struct li *A,*B,*C;
    A=create();
    B=create();
    printf("fdjkasj");
    C=sort(A,B);

    print(C);
    return 0;
}