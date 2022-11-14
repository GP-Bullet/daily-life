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
     printf("后序非递归：");
     PostOreder(bt);
    return 0;
}
// 结点类型定义
typedef struct{
	int weight;
	int parent,lch,rch;
}HTNode,*HuffmanTree;
 
// 找出森林中权值最小的两个
void Select(HuffmanTree HT,int n,int &s1,int &s2) {
	int minum;
	int i;
	for(i=1;i<=n;i++){
		if(HT[i].parent == 0){
			minum = i;
			break;
		}
	}
	for(i = 1;i<=n;i++){
		if(HT[i].parent == 0){
			if(HT[i].weight<HT[minum].weight){
				minum = i;
			}
		}
	}
	s1 = minum;
	for(i=1;i<=n;i++){
		if(HT[i].parent == 0&& i!=s1){
			minum = i;
			break;
		}
	}
	for(i = 1;i<=n;i++){
		if(HT[i].parent == 0&& i!=s1){
			if(HT[minum].weight<HT[minum].weight){
				minum = i;
			}
		}
	}
	s2 = minum;
}
 
// 建立哈夫曼树 
void CreatHuffmanTree(HuffmanTree HT,int n){
	int m,i,s1,s2;
	if(n<=1){
		return ;
	}
	m = 2*n-1;			// 数组共2n-1个元素
	HT = new HTNode[m+1];	// 0号单元未用，HT[m]表示根节点 
	for(i=1;i<=m;i++){		// 将2n-1个元素的lch,rch,parent设置为0 
		HT[i].lch = 0;
		HT[i].rch = 0;
		HT[i].parent = 0;
	} 
	for(i = 1;i<=n;i++){	// 输入前n个元素的weight值 
		scanf("%d",HT[i].weight);
	}
	// 初始化结束，下面开始建立哈夫曼树 
	for(i=n+1;i<=m;i++){
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].weight = HT[s1].weight+HT[s2].weight;
	} 
} 

//存放哈夫曼编码
typedef char** HuffmanCode;
 
// 结点类型定义
typedef struct{
	int weight;
	int parent,lch,rch;
}HTNode,*HuffmanTree; 
 
// 哈夫曼编码 
void  CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
	HC = new char*[n+1];
	char *cd = new char[n];
	cd[n-1] = '\0';
	int start,c,f,i;
	for(i=1;i<=n;i++){
		start = n-1;
		c = i;
		f = HT[i].parent;
		while(f!=0){
			start--;
			if(HT[f].lch == c){
				cd[start] = '0';
			}else{
				cd[start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = new char[n-start];
		strcpy(HC[i],&cd[start]);
	}
	delete cd;		// 释放临时空间 
}



