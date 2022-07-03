//问康宁的过程
//看龙哥代码
//数据结构  链表  二叉树
//功能、
//分页  宏   登录界面
//转二进制图像
//后端的管理系统怎么用于前端
#include<stdio.h>
#include"List.h"


int main(){
    //学生管理系统
    //用户身份
    //管理员身份
    //超级管理员
    // 按学号查询 按性别查询 按姓名查询 按宿舍查询  数据结构
    
}

void Main_Menu9(void) {
	system("clear");
	char choice;
	do { 
		system("clear");
		printf("\n\n==================================================================\n");
		printf("\n========您好，[%s]先生/女士,您的身份是超级管理员。=================\n",gl_CurUser.username);
		printf("\n==================================================================\n");
		printf("     **************** 学生管理管理系统 ****************\n\n");
		printf("      [S]学生添加界面                [P]剧目管理界面\n");
		printf("\n");                  
		printf("      [T]售票管理界面                 [C]查询演出票\n");
		printf("                      \n");
		printf("      [R]学生退学界面                      [Q]查询学生界面\n");
		printf("                       \n");
		printf("      [N]统计学生人数                             \n");
		printf("                       \n");
		printf("      [F]维护个人资料                  [A]管理系统用户\n");
		printf("                       \n");
		printf("\n");
		printf("      [E]退出系统\n");
		printf("\n==================================================================\n");
		printf("\n请输入您要进行的操作");
		
		fflush(stdin);		
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
        fflush(stdin);
		switch (choice)
		{
		case 'S':
		case 's':
            system("clear");
			Studio_UI_MgtEntry();
			break;
        case 'P': 
		case 'p':
            system("clear");
			Play_UI_MgtEntry(); 
			break; 
		case 'F':
		case 'f':
            system("clear");
			MaiAccount_UI_MgtEntry();
			break;
		case 'c': 
		case 'C':
            system("clear");
			Ticket_UI_Query(); 
            break; 
		case 'Q': 
		case 'q': 
			system("clear");
			Schedule_UI_ListAll(); 
			break; 
		case 'T': 
		case 't': 
			system("clear");
			Sale_UI_MgtEntry(); 
			break; 
		case 'R': 
		case 'r': 
			Sale_UI_RetfundTicket(); 
			break; 
		case 'N': 
		case 'n': 
			StaSales_UI_MgtEntry(); 
			break; 
		case 'A': 
		case 'a':
			system("clear");
			Account_UI_MgtEntry();
			break;
		case 'L': 
		case 'l':
			system("clear");
			SalesAnalysis_UI_MgtEntry();
			break;
		}
	} while ('E' != choice && 'e' != choice);
}