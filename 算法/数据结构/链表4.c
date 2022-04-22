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
LinkList ha;

void keydown(){
    int choice=0;
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
            int n;
            printf("要删除第几条信息?");
            scanf("%d",&n);
            Delete(ha,n);//pos
            break;
        case 4:
            printf("------------------查找信息-------------------\n");
            Search(ha,"马梁川");//姓名
            Node*p;
            if(p!=NULL){
            printf("\n*****************查找到的信息如下*************\n");
            printf("姓名： %s\n",p->name);
            printf("学号: %d\n\n",p->number);
    }
            break;
        case 5:
            printf("-------------------总信息数------------------\n");
            printf("\n共有%d条学生消息\n",ListLength(ha));
            break;
        default:
            printf("选择错误，重新输入\n");
            break;

    }
    write(ha,"1.txt");

int main(){
    

    Node*p;
    ha=InitList();
    CreatByRear(ha);
    read(ha,"1.txt");


    while(1){

        menu();
        keydown();
        getchar();
    }
    getchar();

    return 0;
}

