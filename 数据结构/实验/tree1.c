#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
//ABC##DE#G##F###

typedef struct Node
{
    char data;
    struct Node * LChild;
    struct Node * RChild;
}BiTNode, *BiTree;

typedef struct{
    BiTree elem[MAXSIZE];
    int top;
}SeqStack;

SeqStack * InitStack(){
    SeqStack *s;
    s=(SeqStack *)malloc(sizeof(SeqStack));
    s->top=-1;
    return s;
}
int Push(SeqStack * s,BiTree x){
    if(s->top==MAXSIZE-1)return 0;
    else {
        s->top++;
        s->elem[s->top]=x;
        return 1;
    }
}
int IsEmpty(SeqStack * s){
    if(s->top==-1)return 1;
    else return 0;
}
int Pop(SeqStack * s,BiTree * x){//此处为什么用 *
    if(IsEmpty(s))return 0;
    else { 
        *x=s->elem[s->top];
        s->top--;
        return 1;
    }
}
BiTree GetTop(SeqStack * s)
{
    if(IsEmpty(s))return 0;
    else return(s->elem[s->top]);
}


void Visit(char a){
    printf("%c ",a);
}

void CreateBiTree(BiTree *bt)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#') *bt=NULL;
    else
    {
       *bt=(BiTree)malloc(sizeof(BiTNode));
        (*bt)->data=ch;
        CreateBiTree(&((*bt)->LChild));
        CreateBiTree(&((*bt)->RChild));
    }
}


void PrintBiTree(BiTree bt,int h){
    if(bt==NULL)return;
    PrintBiTree(bt->RChild,h+1);
    for(int i=0;i<h;i++)printf("  ");
    printf("%c\n",bt->data);
    PrintBiTree(bt->LChild,h+1);
}


void PreOrder(BiTree bt){
    SeqStack* S;
    BiTree p;
    S=InitStack();p=bt;
    while(p!=NULL || IsEmpty(S)){
        while(p!=NULL)
            {Visit(p->data);Push(S,p);p=p->LChild;}
        if(!IsEmpty(S))
            {Pop(S,&p);p=p->RChild;}
    }

}
void InOrder(BiTree root){
    if(root){
        InOrder(root->LChild);
        Visit(root->data);
        InOrder(root->RChild);
    }
}

void PostOreder(BiTree root){
    SeqStack *S;
    BiTree p,q;
    S=InitStack();p=root;q=NULL;
    while(p!=NULL||!IsEmpty(S)){
        while(p!=NULL||!IsEmpty(S)){
            while(p!=NULL){
                Push(S,p);p=p->LChild;
            }
            if(!IsEmpty(S)){
                GetTop(S);
                if((p->RChild==NULL)||(p->RChild==q)){
                    Pop(S,&p);Visit(p->data);q=p;p=NULL;
                }else{
                    p=p->RChild;
                }
            }
        }
    }
}
//统计叶子结点数目
int leaf(BiTree root){
    int LeafCount;
    if(root==NULL){
        LeafCount =0;
    }else if ((root->LChild==NULL)&&(root->RChild==NULL)){
        LeafCount =1;
    }else{
        LeafCount =leaf(root->LChild)+leaf(root->RChild);
    }
    return LeafCount;
}

//求二叉树高度
int PostTreeDepth(BiTree bt)
{
    int hl, hr, max;
    if(bt!=NULL){
        hl=PostTreeDepth(bt->LChild);
        hr=PostTreeDepth(bt->RChild);
        max=hl>hr?hl:hr;
        return(max+1);
    }   
    else return(0);
}




int main(){
    BiTree bt;
    CreateBiTree(&bt);
    PrintBiTree(bt,PostTreeDepth(bt));

    printf("二叉树的高度为:%d\n",PostTreeDepth(bt));
    printf("二叉树叶子结点的个数为%d\n",leaf(bt));
    printf("先序非递归：");
    PreOrder(bt);
    printf("\n");
    printf("中序递归：");
    InOrder(bt);
    // printf("后序非递归：");
    // PostOreder(bt);
    return 0;
}