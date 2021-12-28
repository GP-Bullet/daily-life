#include"链表2.c"


void menu(){
	//所有文件都同步到文件 
	printf("-------------【学生管理信息】-------------------\n");
	
	printf("\t\t1.录入信息\n");
	printf("\t\t2.浏览信息\n");
	printf("\t\t3.删除信息\n");
	printf("\t\t4.查找信息\n");
    printf("\t\t5.总信息数\n");
    printf("\t\t0.退出系统\n");

	printf("------------------------------------------------\n");
	
}

Node*list;

void keydown(){
    int choice=0;
    struct student data;
    Node* pMove=NULL;
    scanf("%d",&choice);
    switch(choice){
        case 0:
            printf("正常退出\n");
            //
            //
            break;
        case 1:
            printf("------------------录入信息-------------------\n");
            //插到尾部
            //改函数
            InsertRear(ha);
            break;
        case 2:
            printf("------------------浏览信息-------------------\n");
            OutPut(ha);
            break;
        case 3:
            printf("------------------删除信息-------------------\n");
            Delete(ha,);//pos
            break;
        case 4:
            printf("------------------查找信息-------------------\n");
            Search(ha,);//姓名
            break;
        case 5:
            printf("-------------------总信息数------------------\n");
            ListLength(ha);
            break;
        default:
            printf("选择错误，重新输入\n");
            break;

    }
    write(ha,"1.txt");

int main(){
    LinkList ha;

    Node*p;
    ha=
    read(ha,"1.txt");
    while(1){

        menu();
        keydown();

    }
    return 0;
}

