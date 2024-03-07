#include <stdio.h>
#include <stdlib.h>	  
#include <string.h>

/*二叉树（二叉链表存储）相关类型定义*/
typedef char TElemType;	 //假设二叉树元素均为字符
typedef struct BiTNode{
    TElemType data;			  //结点元素 
    struct BiTNode* lchild;	  //左孩子指针 
    struct BiTNode* rchild;	  //右孩子指针 
}BiTNode, *BiTree;;	//二叉树结点与指向二叉树结点的指针 

/*Pre与In设为全局变量*/
char Pre[] = "ABDGEHICFJ";  //前序序列
char In[] =  "GDBHEIAFJC";  //中序序列

/*递归遍历前序存储的结点创建二叉树*/
BiTree BuildTree_pre_in(int pre_start, int pre_end, int in_start, int in_end){
    BiTree T;
    int i, LTreeLen, RTreeLen;
    
    T = (BiTree)malloc(sizeof(BiTNode));  //建立根结点 
    if(!T)
        exit(0);
    T->data = Pre[pre_start];	//遍历前序存储的结点 
    T->lchild = T->rchild = NULL;	//初始化时置空左右孩子指针 
        
    i=in_start;
    while(In[i]!=T->data)	//在中序序列中寻找根结点位置
        i++;	 
    
    LTreeLen = i-in_start;	//左子树长度 
    RTreeLen = in_end - i;	//右子树长度
        
    if(LTreeLen)   //左子树存在
        T->lchild = BuildTree_pre_in(pre_start+1, pre_start+LTreeLen, in_start, i-1);
    
    if(RTreeLen)   //右子树存在
        T->rchild = BuildTree_pre_in(pre_start+LTreeLen+1, pre_end, i+1, in_end);

    return T;
}

/*根据前序序列和中序序列创建二叉树*/
BiTree Algo(){
    int len_pre, len_in;
    BiTree T;
    
    len_pre = strlen(Pre);
    len_in = strlen(In);
    
    T = BuildTree_pre_in(0, len_pre-1, 0, len_in-1);
    
    return T;
}

/*前序遍历二叉树*/
void PreOrderTraverse(BiTree T){
    if(T){
        printf("%c ",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

/*中序遍历二叉树*/
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        printf("%c ",T->data);
        InOrderTraverse(T->rchild);
    }
}

int main(){
    BiTree T;
    printf("二叉树先序序列为：%s\n", Pre);
    printf("二叉树中序序列为：%s\n", In);
    printf("根据先序序列和中序序列创建二叉树...\n");
    T = Algo();
    printf("前序遍历该二叉树 T = ");
    PreOrderTraverse(T);
    printf("\n");
    printf("中序遍历该二叉树 T = ");
    InOrderTraverse(T);
    printf("\n");
    return 0;
}
