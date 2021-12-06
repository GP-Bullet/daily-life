#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Poetry{
    int id;
    char name[20];
    char dynasty[10];
    char author[20];
    char content[20];
    float score;
    struct Poetry*next;
}Poetry;

int main(){
    printf("\n\n\n");
    printf("\t-------------------------------------------\n");
    printf("\t|           欢迎使用诗词信息管理系统          |\n");
    printf("\t-------------------------------------------\n");
    printf("\t|           1-录入诗词信息                  |\n");
    printf("\t|           2-查询诗词信息                  |\n");
    printf("\t|           3-修改诗词信息                  |\n");
    printf("\t|           4-删除诗词信息                  |\n");
    printf("\t|           5-显示所有诗词                  |\n");
    printf("\t|           6-  诗词总数                    |\n");
    printf("\t|           0-  退出程序                    |\n");
    printf("\t--------------------------------------------\n");
    printf("\t请选择功能0-6：")；
    scanf("%d",&choice);
}

void InsertPoetry(Poetry*head,int Poetry_id){
    Poetry*p,*s;
    p=head;
    s=(Poetry*)malloc(sizeof(Poetry));
    s->id=Poetry_id;
    printf("\t=============================================\n");
    printf("            *****添加诗词信息*****               \n");
    printf("\t=============================================\n");
    printf("\t分配给该诗词的编号为：%d\n",Poetry_id);
    printf("\t%s","输入诗词名称：\t");
    scanf("%s",s->name);
    printf("\t%s","输入诗词朝代：\t");
    scanf("%s",s->dynasty);
    printf("\t%s","输入诗词作者：\t");
    scanf("%s",s->author);
    printf("\t%s","输入诗词内容：\t");
    scanf("%s",s->content);
    printf("\t%s","输入诗词关注度：\t");
    scanf("%f",&s->score);
    s->next=NULL;
    p=head;
    while(p->next)
        p=p->next;
    p->next=s;
}


Poetry*FindPoetry(Poetry*head,char name[]){
    Poetry*p;
    p=head->next;
    while(p&&strcmp(p->name,name)!=0){
        p=p->next;
    }
    return p;
}
void PrintPoetry(Poetry*node){
    if(!node)
}
