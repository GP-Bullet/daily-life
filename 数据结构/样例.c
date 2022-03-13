#include"mylist.h"


//菜单设计 
void menu(){
	//所有文件都同步到文件 
	printf("-------------【学生管理信息】-------------------\n");
	printf("\t\t0.退出系统\n");
	printf("\t\t1.录入信息\n");
	printf("\t\t2.浏览信息\n");
	printf("\t\t3.修改信息\n");
	printf("\t\t4.删除信息\n");
	printf("\t\t5.查找信息\n");
	printf("------------------------------------------------\n");
	
}
struct Node* list;
//用户的交互
//根据所选的菜单项，作相应的事情 
void keyDown(){
	
	int choice = 0;
	struct student data;
	struct Node* pMove = NULL;
	scanf("%d",&choice);
	switch(choice){
		case 0:
			printf("正常退出！\n");
			system("pause");
			exit(0);
			break;
		case 1:
			printf("-------------录入信息-------------------\n");
			//插入链表 
			fflush(stdin);	//清空缓冲区！！！！！！！！！ 
			printf("请输入学生的\n姓名、年龄、性别、电话：\n");
			scanf("%s%d%s%s",data.name,&data.age,data.sex,data.tel);
			insertNodeByHead(list,data); 
			break;
		case 2:
			printf("-------------浏览信息-------------------\n");
			printList(list);	//打印链表
			break;
		case 3:
			printf("-------------修改信息-------------------\n");
			printf("请输入要修改信息的学生姓名：");
			scanf("%s",data.name);
			reviseInfoByData(list,data.name); 
			break;
		case 4:
			printf("-------------删除信息-------------------\n");
			printf("请输入删除学生的姓名：");
			scanf("%s",data.name);
			deleteNode(list,data.name);
			break;
		case 5:
			printf("-------------查找信息-------------------\n");
			printf("请输入要查找学生的姓名：");
			scanf("%s",data.name);
			if( pMove = searchInfoByData(list,data.name)){
				printf("姓名\t年龄\t性别\t电话\n"); 
				printf("%s\t%d\t%s\t%s\n",pMove->data.name,pMove->data.age,pMove->data.sex,pMove->data.tel);
			}
			break;
		default:
			printf("选择错误，重新输入\n");
			system("pause");
			break; 
	}
	writeInfoToFile(list,(char*)"1.txt");
} 
int main(){
	list = createList();
	readInfoFromFile(list,(char*)"1.txt");
	while(1){
		
		menu();
		keyDown();

	} 
	return 0;

