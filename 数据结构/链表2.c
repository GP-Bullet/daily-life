//链表的初始化、创建和输出
//和数组对应起来
#include<stdlib.h>
#include<stdio.h>
#include<string.h>




typedef struct node{
    char name[40];
    int number;
    struct node* next;

}Node,*LinkList;

//LinkList是结构体指针类型
//LinkList head相当于Node*head,也相当于struct node *head


//*初始化
LinkList InitList(){
    LinkList head;//头（结构体）指针， 而指针是类似于结点类型的指针    //而结点则不是指针，结点是一块内存空间
    head=(Node *)malloc(sizeof(Node)); //头指针指向头结点   
    head->next=NULL;
      //因head是指针才用->
    return head;   //返回头指针的地址,即头结点

}

//*尾插法
void CreatByRear(LinkList head){//与数组类似，把头传进去
    Node *r,*s;//r指向最后一个结点//临时指针
    char name[20];
    int number;
    r=head;
    printf("请输入学生的姓名和学号：\n");
    while(1){//for   or   while  哪个好
        scanf("%s",name);//先输到栈中
        scanf("%d",&number);
        if(number==0)
            break;

        s=(Node *)malloc(sizeof(Node));//新节点
        strcpy(s->name,name);//字符串不能赋值，所以用strcpy     string copy的缩写,把name复制到s->name中
        s->number=number;


        //这两行的区别？
        r->next=s;//指向新结点,构成逻辑相邻

        r=s;//与r=head对应，保证r是指向最后一个结点，为了往下运行，构成一个循环形态
    }
    r->next=NULL;//出循环后，rnext不再有下个结点
}

//*头插法
void CreatByHead(LinkList head){
    Node *s;
    char name[20];
    int number;
    printf("请输入学生的姓名和学号：\n");
    while(1){
        scanf("%s",name);
        scanf("%d",&number);
    
    if(number==0) break;
    s=(Node *)malloc(sizeof(Node));
    strcpy(s->name,name);
    s->number=number;


    s->next=head->next;//next即null或后一个结点

    head->next=s;//头结点指向新结点
    }
}

//*输出
void OutPut(LinkList head){
    Node *p;
    p=head->next;
    printf("学生信息如下\n");
    while(p){
        
        printf("姓名：%s\n",p->name);
        printf("学号：%d\n\n",p->number);
        p=p->next;
    }
}

//*插入
void Insert(LinkList head,int i){//第几个位置
    Node *p=head,*s;

    int j=0;//?怎么老喜欢用while
    while(j<i-1 && p){
        p=p->next;
        j++;
    }//找到第i-1个结点的地址p
    if(p){
        printf("请输入待添加学生的姓名和学号：\n");
        s=(Node*)malloc(sizeof(Node));
        scanf("%s",s->name);
        scanf("%d",&s->number);
        
        s->next=p->next;//next相当该节点的下一个结点，类似于a[i++]
        p->next=s;//p直接代表了那块内存 
    }
}
//*表首添加结点
//*表尾添加结点
void InsertRear(LinkList head){
    Node*p=head,*s;
    while(p && p->next)
        p=p->next;
    if(p){
        printf("请输入待添加学生的姓名和学号:\n");
        s=(Node*)malloc(sizeof(Node));
        scanf("%s",s->name);
        scanf("%d",&s->number);
        p->next=s;
        s->next=NULL;
    }
}

//*删除
void Delete(LinkList head,int pos){
    Node *p=head,*q;
    int j=0;
    printf("\n********************删除第%d个学生*********************\n",pos);
    while(j<pos-1&&p){
        p=p->next;
        j++;
    }
    if(p==NULL||p->next==NULL)
        printf("the position is ERROR!");
    else{
        q=p->next;
        p->next=q->next;
        free(q);
    }
}

//*查询
Node *Search(LinkList head,char name[]){//?[]可以吗
    Node *p=head->next;
    while(p){
        if(strcmp(p->name,name)!=0){
            p=p->next;
        }else{
            break;}
    }
    if(p==NULL)
        printf("没有找到值为%s的结点！\n",name);
    return p;
}

//*长度
int ListLength(LinkList head){
    int count=0;
    Node *p;
    p=head->next;
    while(p){
        count++;
        p=p->next;
    }
    return count;
}



//文件读操作
void read(Node*head,char* filename){
    //1、打开文件
    FILE*fp;

    fp=fopen(filename,"r");
    if(fp==NULL){
        fopen(filename,"w+");
    }
    //2read
    while()



    //3.close
    fclose(fp);

}

void write(Node*head,char*filename){
    //1.打开文件
    FILE*fp;
    fp=fopen(filename,"w");

    //2.写文件
    while()

    //3.关闭文件
    fclose(fp);
}


int main(){
    LinkList ha;
  //  LinkList hb;
    //hb=InitList();
    //CreatByHead(hb);
    //OutPut(hb);
    Node*p;
    ha=InitList();
    CreatByRear(ha);
    OutPut(ha);

    Insert(ha,1);
    OutPut(ha);

    
//    Delete(ha,4);Z
//    OutPut(ha);




    
    
}

