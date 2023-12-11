#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct stu{
    char num[20];
    char name[40];
    char sex[5];
};

int main(){
    struct stu class[40];
    FILE*fp;
    int i;
    printf("\n输入该班的数据：\n");
    fp=fopen("class_list.txt","wt");
    if(fp==NULL){
        printf("不能打开此文件，按任意键退出！");
        getchar();
        exit(1);
    }
    for(i=0;i<5;i++){
        printf("\n第%d个人的信息：\n",i+1);
        printf("\n学号：");
        gets(class[i].num);
        printf("\n姓名：");
        gets(class[i].name);
        printf("\n性别：");
        gets(class[i].sex);
        fprintf(fp,"%s %s %s\n",class[i].num,class[i].name,class[i].sex);

    }
    fclose(fp);
    fp=fopen("class_list.txt","rt");
    printf("班里数据为：\n");
    printf("学号 姓名 性别\n");
    i=0;
    while(fscanf(fp,"%s %s %s",class[i].num,class[i].name,class[i].sex)!=EOF){
        printf("%s %s %s\n",class[i].num,class[i].name,class[i].sex);
        i++;
    }
    fclose(fp);

return 0;
}