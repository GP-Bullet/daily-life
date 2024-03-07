#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    char data;
    struct Node * LChild;
    struct Node * RChild;
}BiTNode, *BiTree;




void CreateBiTree(BiTree *bt)
{
    char ch;
    ch=getchar();
    if(ch=='.') *bt=NULL;
    else
    {
       *bt=(BiTree)malloc(sizeof(BiTNode));
       (*bt)->data=ch;
       CreateBiTree(&((*bt)->LChild));
       CreateBiTree(&((*bt)->RChild));
    }
}


//先序遍历
void PreOrder(BiTree root)
{
    if (root!=NULL)
{
      printf("%c ",root ->data);
 PreOrder(root ->LChild);
 PreOrder(root ->RChild);
}
}
//中序遍历
void InOrder(BiTree root)
{
    if(root != NULL)
    {
        InOrder(root->LChild);
        printf("%c ",root ->data);
        InOrder(root->RChild);
    }
}
//后序遍历
void PostOrder(BiTree root)
{
    if(root!=NULL)
{
   PostOrder(root ->LChild);
   PostOrder(root ->RChild);
   printf("%c ",root ->data);
}
}
//统计叶子结点数目
int leaf(BiTree root)
{
     int LeafCount;
     if(root==NULL)
        LeafCount =0;
      else if ((root->LChild==NULL)&&(root->RChild==NULL))
                   LeafCount =1;
 else
            LeafCount =leaf(root->LChild)+leaf(root->RChild);
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






int main()
{
    printf("请输入：");
    int Case=10;
    while(Case--)
    {
        BiTree tree;
        CreateBiTree(&tree);
        printf("\nPreOrder:\n");
        PreOrder(tree);
        printf("\nInOrder:\n");
        InOrder(tree);
        printf("\nPostOrder:\n");
        PostOrder(tree);


        printf("\n叶子结点数目：%d\n",leaf(tree));


        printf("\n二叉树的高度：%d\n",PostTreeDepth(tree));
    }




}