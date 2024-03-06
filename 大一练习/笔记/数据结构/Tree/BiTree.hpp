#include<iostream>
using namespace std;
typedef struct BiTNode{
    TelemType data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode,*BiTree;

void InitBiTree(BiTree &BT){
    BT=NULL;
}
void CreateBiTree(BiTree &BT){
    TelemType a;
    cin>>a;
    if(a==Nil){
        BT=NULL;
    }else{
        BT=(BiTree)malloc(sizeof(BiTree));
        if(!BT)
            exit(1);
        BT->data=a;
        CreateBiTree(BT->lchild);
        CreateBiTree(BT->rchild);
    }
}
bool BiTreeEmpty(BiTree BT){
    if(BT){
        return false;
    }else{
        return true;
    }
}



