#include<stdio.h>
#include<stdlib.h>
#include"stack.hpp"

typedef struct Node
{
    char data;
    struct Node * LChild;
    struct Node * RChild;
}BiTNode, *BiTree;

void Visit(char a){
    printf("%c\n",a);
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
    SqStack S;
    BiTree p;
    InitStack_Sq(S,1000,10);p=bt;
    while(p!=NULL||StackEmpty_Sq(S)){
        while(p!=NULL){
            Visit(p->data);
            Push_Sq(S,p);
            p=p->LChild;
        }
        if(!StackEmpty_Sq(S)){
            Pop_Sq(S,&p);
            p=p->RChild;
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
  if(bt!=NULL)
  {
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
    PrintBiTree(bt,5);
    return 0;
}