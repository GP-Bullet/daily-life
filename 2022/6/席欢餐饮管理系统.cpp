#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
void creatHeadnode(); 
void menu();
void luru(struct node *phead);
void printf(struct node *phead);
void output(struct node *p);
void shanchu(struct node *phead);
void info_output(struct node *pfind);
struct node * chazhaonode(struct node *phead,char name[20]);
void chazhao();
void xiugai();
struct node *chazhao1();
struct node *chazhao2();
void tongji(struct node *phead);
void baocun(struct node *phead);
void shengxu(struct node *head);
void jiangxu(struct node *head);
void sort();
void paixu();
void chakan();
void baocun(struct node *phead);
void read(struct node *phead,FILE *fp);
void write(struct node *phead,FILE *fp);
void zhuce();
void denglu();
struct node  
{
	char name[100];
	int id;
	int price;
	char kinds[100];
	struct node *next;
};
typedef struct user
{
	char name[20];
	char password;
}user;
struct node *phead=NULL;
void creatHeadnode()
{
	phead=(struct node *)malloc(sizeof(struct node));
	if(!phead)
	{
		printf("ͷ������ʧ��"); 
	}
	phead->next=NULL;
}
int main()
{
	system("color B0");
	creatHeadnode();
	
	while(1)
	{
		int choice;
		menu();
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:luru(phead);break;
			case 2:printf(phead);break;
			case 3:baocun(phead);break;
			case 4:shanchu(phead);break;
			case 5:chazhao();break;
			case 6:xiugai();break;
			case 7:paixu();break;
			case 8:tongji(phead);break;
			case 9:chakan();break;
			case 0:printf("Bye Bye�����ǣ��´��ټ�������");
			       system("pause");system("cls");
				   break;
			default:
			       printf("����������������������");
				   system("pause");
				   system("cls");
				   break;
		}
    }
	return 0;
}

void menu()
{
	printf("*********************************************\n");
	printf("*                                           *\n");
	printf("*               ��ӭ��������ϵͳ ^-^        *\n");
    printf("*********************************************\n");
	printf("*\t\t--1.¼����Ϣ--              *\n");
	printf("*\t\t--2.��ӡ��Ϣ--              *\n");
	printf("*\t\t--3.������Ϣ--              *\n");
	printf("*\t\t--4.ɾ����Ϣ--              *\n");
	printf("*\t\t--5.������Ϣ--              *\n");
	printf("*\t\t--6.�޸���Ϣ--              *\n");
	printf("*\t\t--7.��������--              *\n");
	printf("*\t\t--8.����ͳ��--              *\n");
	printf("*\t\t--9.�鿴�˵�--              *\n"); 
	printf("*\t\t--0.�˳�ϵͳ--              *\n");
	printf("*********************************************\n");
	printf("    ��ѡ��0-9��: "); 
}
void luru(struct node *phead)
{
	struct node *pnew=NULL;
	struct node *pfind=phead;
	while(pfind->next!=NULL)
	{
		pfind=pfind->next;
	}
	pnew=(struct node *)malloc(sizeof(struct node));
	printf("��������Ʒ��ţ�\n");
	scanf("%d",&pnew->id);
	printf("��������Ʒ���ƣ�\n");
	scanf("%s",pnew->name);
	printf("��������Ʒ�۸�\n");
	scanf("%d",&pnew->price);
	printf("��������Ʒ���\n");
	scanf("%s",pnew->kinds);
	pnew->next=NULL;
	pfind->next=pnew;
	printf("%s����Ʒ���ӳɹ���\n",pnew->name);
	system("pause");
	system("cls");
	
}
void printf(struct node *phead)
{
	system("pause");
	system("cls");
	printf("*********************************************\n");
 	printf("            ��ӭ������������ϵͳ      \n");
    printf("*********************************************\n");
    printf("\t*���*\t\t*����*\t\t*�۸�*\t\t*���*\n");
	struct node *pfind=phead->next;
	while(pfind!=NULL)
	{
		output(pfind);
		pfind=pfind->next;
	}
	system("pause");
	system("cls");
}
void output(struct node *pfind)
{
	printf("************************************************\n");
    printf("\t%d\t\t%s\t\t%d\t\t%s\n",pfind->id,pfind->name,pfind->price,pfind->kinds);
     	
}
void shanchu(struct node *phead)
{ 
    char name[20];
	struct node *target=NULL;
	struct node *pfind=phead;
	struct node *ptemp=NULL;
	printf("����������Ҫɾ�������ƣ�\n");
	scanf("%s",name);
	target=chazhaonode(phead,name);
	if(target==NULL)
	{
		printf("�Բ��𣬲��޴˼�¼��\n");
		return;
	}
	else
	{
		ptemp=target->next;
		while(pfind->next!=target)
		{
			pfind=pfind->next;
		}
		free(target);
		target=NULL;
		pfind->next=ptemp;
		printf("ɾ���ɹ���\n");
	}
}
struct node *chazhaonode(struct node *phead,char name[20])
{
	struct node *pfind=phead;
	while(pfind!=NULL)
	{
		if(strcmp(pfind->name,name)==0)
		{
			return pfind;
		}
		pfind=pfind->next;
	}
	return pfind;
}
void chazhao()
{
	int choice,b;
	char a[20];
	printf("��ѡ����Ҫ���ҵķ�ʽ��\n");
	printf("1.����Ʒ������\n");
	printf("2.����Ʒ�۸����\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		    {
		       chazhao1();
	           break;
			}
		case 2:
		   {
		   	   chazhao2();
		       break;
		   }
	}
}
struct node *chazhao1()
{
	system("cls");
	int i;
	char a[20];
	printf("����������Ҫ���ҵ���Ʒ����");
	scanf("%s",a);
	struct node *p=phead;
	while(p!=NULL)
	{
		if(strcmp(a,p->name)==0) 
		{
			i=1;
			printf("*********************************************\n");
            printf("\t*���*\t\t*����*\t\t*�۸�*\t\t*���*\n");
            printf("\t %d \t\t%s\t\t%d\n",p->id,p->name,p->price,p->kinds);
		}
		p=p->next; 
	}
	if(i=0)
	{
		printf("�Բ��𣡲��޴���"); 
	}
	system("pause");
	system("cls");
}
struct node *chazhao2()
{
	system("cls");
	int a,b;
	printf("����������Ҫ���ҵļ۸�");
	scanf("%d",&b);
	struct node *p=phead;
	while(p!=NULL)
	{
		if(b==p->price) 
		{
			a=1;
			printf("*********************************************\n");
            printf("\t*���*\t\t*����*\t\t*�۸�*\t\t*���*\n");
            printf("\t%d\t\t%s\t\t%d\n",p->id,p->name,p->price,p->kinds);
		}
		p=p->next; 
	}
	if(a=0)
	{
		printf("�Բ��𣡲��޴���"); 
	}
	system("pause");
	system("cls");
}
void xiugai()
{
	char name[20];
	int target=NULL;
	printf("����������Ҫ�޸ĵ���Ʒ���ƣ�");
	scanf("%s",name);
	struct node *p=phead;
	while(p!=NULL)
	{
		if(strcmp(name,p->name)==0)
		{
			printf("�������޸ĺ�ļ۸�");
			scanf("%d",&p->price);
		}
		p=p->next;
	}
	printf("�޸ĳɹ���\n"); 
	system("pause");
	system("cls");
}
void tongji(struct node *phead)
{
	int count=0;
	struct node *p;
	p=phead;
	while(p)
	{
		count++;
		p=p->next;
	}
	printf("��һ��������%d����Ʒ\n",count-1);
	system("pause");
	system("cls");
} 
void paixu()
{

	printf("*********************************************\n");
	printf("*                                           *\n");
    printf("*\t      ��ѡ����Ҫ�鿴�ķ�ʽ          *\n");
	printf("*                                           *\n");
	printf("*********************************************\n");
	printf("*                                           *\n");
	printf("*\t\t1.�۸�ӵ͵���              *\n");
	printf("*                                           *\n");
	printf("*\t\t2.�۸�Ӹߵ���              *\n");
	printf("*                                           *\n");
	printf("*********************************************\n");
	int t;
	scanf("%d",&t);
    switch(t)
    {
    	case 1:shengxu(phead);break;
    	case 2:jiangxu(phead);break; 
	}
}
void jiangxu(struct node *phead)
{
	system("cls");
	node a[100];
	node temp;
	int i,j,n=0;
	struct node *p=phead->next;
	while(p!=NULL)
	{
		strcpy(a[n].name,p->name);
		a[n].price=p->price;
		n++;
		p=p->next;
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j].price<a[j+1].price)
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		printf("*********************************************\n");
        printf("*\t*����*\t\t*�۸�*\t\t*���*\n");
		printf("\t%s\t\t%d\n",a[i].name,a[i].price,a[i].kinds);
		
	}
	system("pause");
	system("cls");

}
void shengxu(struct node *phead)
{
	system("cls");
	node a[100];
	node temp;
	int i,j,n=0;
	struct node *p=phead->next;
	while(p!=NULL)
	{
		strcpy(a[n].name,p->name);
		a[n].price=p->price;
		n++;
		p=p->next;
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j].price>a[j+1].price)
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		
		printf("*********************************************\n");
        printf("*\t*����*\t\t*�۸�*\t\t*���*\n");
		printf("\t%s\t\t%d\n",a[i].name,a[i].price,a[i].kinds);
	}
	system("pause");
	system("cls");
}
void write(struct node *phead,FILE *fp)
{   
    FILE *f=fp;
    struct node *p = phead->next;
	while(p!=NULL)
	{
		fprintf(fp,"%d\t%s\t%d\t%s\n",p->id,p->name,p->price,p->kinds);
		p=p->next;
	}
	fclose(f);
}
void baocun(struct node *phead)
 {
 	
 	FILE *fp;
 	int choice;
 	system("cls");
 	printf("����Ҫ����Ϣ��������һ�� \n");
 	printf("        ------------     \n");
	printf("        | 1.������ |     \n");
	printf("        | 2.���   |     \n");
	printf("        | 3.�̲�   |     \n");
	printf("        | 4.����� |     \n");
	printf("        | 5.����   |     \n");
	printf("        ------------     \n"); 
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:fp=fopen("C:\\Users\\29917\\Desktop\\������.txt","a");break;
		case 2:fp=fopen("C:\\Users\\29917\\Desktop\\���.txt","a");break;
		case 3:fp=fopen("C:\\Users\\29917\\Desktop\\�̲�.txt","a");break;
		case 4:fp=fopen("C:\\Users\\29917\\Desktop\\�����.txt","a");break;
		case 5:fp=fopen("C:\\Users\\29917\\Desktop\\����.txt","a");break;
	}
	write(phead,fp);
	printf("���ݱ���ɹ���"); 
	system("pause");
	system("cls");
	
 }
void chakan()
{
	system("cls");
   	FILE *fp;
	int choice;
	char s[20];
	char *p=s;
	printf("*****************************\n");
	printf("----��ӭ���ٰ�������Ʒ��-----\n");
	printf("*****************************\n");
	printf("           @�˵�@        \n");
	printf("        ------------     \n");
	printf("        | 1.������ |     \n");
	printf("        | 2.���   |     \n");
	printf("        | 3.�̲�   |     \n");
	printf("        | 4.����� |     \n");
	printf("        | 5.����   |     \n");
	printf("        ------------     \n"); 
	printf("*****************************\n");
    printf("��ѡ����Ҫ�鿴�ı�ţ�1~5����");
	scanf("%d",&choice);
    switch(choice)
	{
			case 1:
			{
			    fp=fopen("C:\\Users\\29917\\Desktop\\������.txt","r");
			    break;
		    }
			case 2:
			{
			    fp=fopen("C:\\Users\\29917\\Desktop\\���.txt","r");
			    break;
		    }
			case 3:
			{
			     fp=fopen("C:\\Users\\29917\\Desktop\\�̲�.txt","r");
			     break;
			}
			case 4:
			{
			     fp=fopen("C:\\Users\\29917\\Desktop\\�����.txt","r");
			     break;
			}
			case 5:
			{
				 fp=fopen("C:\\Users\\29917\\Desktop\\����.txt","r");
			     break;
			}
	}
	 printf("*************************************\n");
	 printf(" ���   ��Ʒ��        �۸�/Ԫ   ���\n"); 
	 printf("*************************************\n");
     while((p = fgets(s,100,fp)) != NULL)
	{ 
	            
	    printf("%s",s); 
    
    }  
	printf("**************************************\n");         
	fclose(fp);
	system("pause");
	system("cls");
}

