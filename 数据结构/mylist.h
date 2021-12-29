#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 

//数据的设计-----》学生信息抽象出
struct student{
	char name[20];
	int age;
	char sex[5];
	char tel[20];
	
//	int math;
//	int english;
};//结构
//测试的结构 
struct Node{
	struct student data;
	struct Node* next;
}; 
//创建表头 
struct Node* createList(){
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
}
//创建节点 
struct Node* createNode(struct student data){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
} 
//插入结点(表头法)
void insertNodeByHead(struct Node* headNode, struct student data){
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next; 
	headNode->next = newNode;
}
//指定位置删除
void deleteNode(struct Node* headNode,char* name){
	struct Node* posFrontNode;
	struct Node* posNode;
	if(headNode->next == NULL){
		printf("链表为空！\n");
		return; 
	}
	posFrontNode = headNode;
	posNode = headNode->next;
	while(posNode && strcmp(posNode->data.name,name)){
		posFrontNode = posNode;
		posNode = posFrontNode->next;
	}
	if(!posNode){
		printf("您要删除的数据不存在！\n"); 
		return;
	}
	if(!strcmp(posNode->data.name,name)){
		posFrontNode->next = posNode->next;
		free(posNode);
	}
} 
//查找功能
struct Node* searchInfoByData(struct Node* headNode,char* name) {
	struct Node* posNode;
	if(headNode->next == NULL){
		printf("链表为空！\n");
		return NULL; 
	}
	posNode = headNode->next;
	while(posNode && strcmp(posNode->data.name,name)){;
		posNode = posNode->next;
	}
	if(!posNode){
		printf("您要查找的数据不存在！\n"); 
		return NULL;
	}
	return posNode; 
}
//修改功能
void reviseInfoByData(struct Node* headNode,char* name) {
	struct Node* posNode;
	if(headNode->next == NULL){
		printf("链表为空！\n");
		return; 
	}
	posNode = headNode->next;
	while(posNode && strcmp(posNode->data.name,name)){;
		posNode = posNode->next;
	}
	if(!posNode){
		printf("您要修改的数据不存在！\n"); 
		return;
	}
	printf("请输入学生[%s]的年龄、性别、电话：\n",posNode->data.name);
	scanf("%d%s%s",&posNode->data.age,posNode->data.sex,posNode->data.tel);
}
//文件读操作
void readInfoFromFile(struct Node* headNode,char* fileName){
	//1.打开文件
	FILE *fp;
	struct student data;
	fp = fopen(fileName,"r");
	if(fp == NULL){
		fopen(fileName,"w+");//打开文件具有创建功能 
	}
	//2.读文件 
	while(fscanf(fp,"%s\t%d\t%s\t%s\n",data.name,&data.age,data.sex,data.tel)!=EOF){
		insertNodeByHead(headNode,data); 
	}
	//3.关闭文件
	fclose(fp);
}
//文件写操作
void writeInfoToFile(struct Node* headNode,char* fileName){
	//1.打开文件
	FILE *fp;
	fp = fopen(fileName,"w");
	struct Node* pMove = headNode->next;
	
	//2.写文件 
	while(pMove){
		fprintf(fp,"%s\t%d\t%s\t%s\n",pMove->data.name,pMove->data.age,pMove->data.sex,pMove->data.tel);
		pMove = pMove->next;
	}
	//3.关闭文件
	fclose(fp);
}

//打印链表
void printList(struct Node* headNode){
	struct Node* pMove = headNode->next;
	//设计列数据的处理
	printf("姓名\t年龄\t性别\t电话\n"); 
	while(pMove){
		printf("%s\t%d\t%s\t%s\n",pMove->data.name,pMove->data.age,pMove->data.sex,pMove->data.tel);
		pMove = pMove->next;
}


