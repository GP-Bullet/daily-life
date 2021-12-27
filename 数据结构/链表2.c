#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//链表占的内存？

typedef struct node{
    char name[40];
    int number;
    struct node* next;

}Node,*LinkList;

//LinkList是结构体指针类型
//LinkList head相当于Node*head,也相当于struct node *head
//尾插法
LinkList InitList(){
    LinkList head;//头（结构体）指针， 而指针是类似于结点类型的指针    //而结点则不是指针，结点是一块内存空间
    head=(Node *)malloc(sizeof(Node)); //头指针指向头结点   
    head->next=NULL;
      //因head是指针才用->
    return head;   //返回头指针的地址,即头结点

}

void CreatByRear(LinkList head){
    Node *r,*s;//r指向最后一个结点//临时指针
    char name[20];
    int number;
    r=head;
    printf("请输入学生的姓名和学号：\n");
    while(1){
        scanf("%s",name);//先输到栈中
        scanf("%d",&number);
        if(number==0)
            break;

        s=(Node *)malloc(sizeof(Node));//新节点
        strcpy(s->name,name);//字符串不能赋值，所以用strcpy     string copy的缩写,把name复制到s->name中
        s->number=number;


        //这两行的区别？
        r->next=s;
        r=s;//与r=head
    }
    r->next=NULL;
}