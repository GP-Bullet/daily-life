#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>  //用于*输入密码
struct user *head_c; //用户和管理者链表的链表头 
int id=0; //判断是用户还是管理者 
int notice_cnt=0; //有多少条notice 
int message_cnt=0; //有多少条message 
char tmp_zh[100];
char now_user[100],now_manager[100];  //现在的用户或管理者
char sudo[20]="boss"; //超级密码 
struct medicine *head; //药品的链表头 
struct medicine   //药结构体 
{
    char num[10];
    char name[100];
    double price;
    int cnt;
    double total;
    struct medicine * next;
} med;
struct user //人结构体 
{
    struct user*next;
    char  zh[30];
    char mm[30];
    
};
void init_medicine();
void show_notice();
void show_all();
int password(char *zh);
void check_good();
void message();
void purchase();
void show_message();
void add();
void dlete_medicine();
void dlete_user();
void modify();
void check_income();
void notice();
void menu_consumer();
void menu_manager();
void mod_pwd();
void get_pwd(char *buf);
void login_user();
void init_user();
void sign_up_user();
void destory_user();
void destory_medicine();
void insert_medicine();
void logout();
void down_sort(struct medicine * L,int flag);
void up_sort(struct medicine * L,int flag);
void dlete_manager();
void add_manager();
void logout();
void Welcome()  //欢迎菜单 
{   

   fflush(stdin);
    id=0;  
    printf("*   *   *  * * *      *        *  *      *         *  *      * * *\n");
    printf(" * * * *   * *        *      *        *     *    *  *  *     * *\n" );
    printf("  *   *    * * *      * * *    *  *      *      *       *    * * * \n");
    printf("欢迎来到西邮药店！\n");
    printf("请选择你的身份\n");
    printf("1.消费者         2.管理者\n");
    scanf("%d",&id);
     char c;
     if((c=getchar())!='\n')
     {
     	printf("输入错误！\n");
    	Welcome();
	 }
     
    if(id!=1&&id!=2)
    {
    	printf("输入错误！\n");
    	Welcome();
	}
   
    destory_medicine(); //摧毁原有链表
    destory_user;
    init_user();  //初始化链表
    init_medicine();
    login_user();  //登录界面

    if(id==1)
    {   
        menu_consumer();
    }
    else if(id==2)
    {  
        menu_manager();
    }
    
    else
    {    
         printf("请输入正确的操作\n");
        
    }
     Welcome();


}
void menu_consumer() //用户菜单 
{   int flag=0;
    if(notice_cnt!=0)
	show_notice();
    printf("你好消费者 %s，请选择你的服务！\n",now_user);
    printf(" 1.查询本店药品\n");
    printf(" 2.给商家留言\n");
    printf(" 3.购买药品\n");
    printf(" 4.展示本店已有药品清单\n");
    printf(" 5.修改密码\n");
    printf(" 6.注销账户\n");
    printf(" 7.退出\n");
    scanf("%d",&flag);
    switch(flag)
    {
        case 1: check_good();break;
        case 2: message();break;
        case 3: purchase();break;
        case 4: show_all();break; 
        case 5: mod_pwd();break;
        case 6: logout();break;
        case 7: Welcome();break; 
        default: printf("请输入正确的操作\n");menu_consumer();break;
        
    }
    if(flag==6)
    {
    	Welcome();
	}
    menu_consumer();

}
int password(char *zh)  //登录密码验证 
{   
	
	char buf[18];
    char tm_zh[20],pwd[20];
	FILE*fp;
    if(id==1)
    fp=fopen("consumer.txt","r");
    else if(id==2)
    fp=fopen("manager.txt","r");
	 while(!feof(fp))
    {
        fscanf(fp,"%s %s",tm_zh,pwd);
        if(strcmp(zh,tm_zh)==0)
        {   
            break;
        }
    }
	fclose(fp); 
	int len=0;
	int cnt=3;
	memset(buf,0,sizeof(buf));
	while(cnt!=0)
	{
		char c=_getch();
		if(c=='\r')
		{  
            cnt--;
			if(strcmp(pwd,buf)==0)
			{   memset(buf,0,sizeof(buf));
				return 1;
			}
			else
			{   len=0;
                printf("buf=%s\n",buf);
				printf("你还有%d次机会\n",cnt);
				memset(buf,0,sizeof(buf));
			}
			
		}
		else if(c=='\b')//回退
		 {
		 	printf("\b \b");
		 	if(len>0)
		 	{    len--;
                 buf[len]='\0';
		 	 
            }
		  } 
		  else
		  {
		  	buf[len++]=c;
		  	printf("*");
		  }
	}
	return 0;
}
void menu_manager()  //管理者菜单 
{
     int flag=0;
     
    printf("你好生产者 %s，请选择你的服务！\n",now_manager);
    if(message_cnt!=0)
    {
    	printf("有消费者留言，请注意查收!\n");
	}
    printf(" 1.上新药品\n");
    printf(" 2.下架药品\n");
    printf(" 3.修改药品\n");
    printf(" 4.插入药品\n"); 
    printf(" 5.查看收益\n");
    printf(" 6.发布公告\n");
    printf(" 7.修改密码\n");
    printf(" 8.管理用户账户\n"); 
    printf(" 9. 查看留言！\n");
    printf(" 10.删除管理者！\n");
    printf(" 11.退出\n");
    scanf("%d",&flag);
    switch(flag)
    {
        case 1: add();break;
        case 2: dlete_medicine();break;
        case 3: modify();break;
        case 4:insert_medicine();break;
        case 5:check_income();break;
        case 6: notice();break;
       case 7: mod_pwd();break;
       case 8:dlete_user();break;
       case 9: show_message();break; 
       case 10: dlete_manager();break;
       case 11: Welcome();break;
        default: printf("请输入正确的操作\n");menu_manager();break;
        
    }
    menu_manager();
}
int main() 
{   system("color A5"); //绿底 
    
    Welcome();
}
void init_medicine() //初始化药品的链表 
{   FILE *fp;
head=(struct medicine *)malloc(sizeof(struct medicine));
head->next=NULL;
struct medicine *q;
  q=head;
    q->next=NULL;
    fp=fopen("medicine.txt","r");
    if(fp==NULL)
    {
    printf("不能打开此文件！");
    //quit();
    }
    while(!feof(fp))
    {   struct medicine *p=(struct medicine *)malloc(sizeof(struct medicine));
        fscanf(fp,"%s %s %lf",p->num,p->name,&p->price);
        
        q->next=p;
        q=p;
    }
    q->next=NULL;
    fclose(fp);
}
void destory_medicine()  //摧毁药品链表 
{
    struct medicine *p=head;
    while(p)
    {
        struct medicine *q=p->next;
        free(p);
        p=q;
    }

}
void add()  //添加药品   
{   
    printf("当编号输入0 退出add\n");
    char bh[10];
    char mz[10];
    double jg;
    struct medicine *p=head->next;
    while(p&&p->next)  //遍历到尾部
    {   
        p=p->next;
    }
    FILE* fp,*fq;
    fp=fopen("medicine.txt","a+");
     fq =fopen("money.txt","a+");
    while(scanf("%s",bh)==1&&strcmp(bh,"0")!=0)
     {   int flag=0; 
	    struct medicine *r=head->next;
        while(r)
        {
            if(strcmp(r->num,bh)==0)
            {  flag=1;
               char clear[20];
               double cl;
               scanf("%s %lf",clear,&cl);
                printf("已经有此药品！\n");
                break;
            }
            r=r->next;
        }
        if(flag==1)
        continue;
        struct medicine * q=(struct medicine *)malloc(sizeof(struct medicine));
        scanf("%s %lf",q->name,&q->price);
         if(q->price<0)
         {  free(q); 
            printf("定价不能为负数！\n");
            continue;
         }
         
        q->next=NULL;
        strcpy(q->num,bh);

        p->next=q;
        p=q;
        fprintf(fp,"%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price);
        fprintf(fq,"%-8s\t %-8s\t %-8.2f\t %-8d\t %-8.2f\t\n",p->num,p->name,p->price,p->cnt,p->total);
            
   }
    p->next=NULL;
    fclose(fp);
    fclose(fq);
}
void  check_good() //查询药品 
{   
    int select,flag=0;
    printf("    亲爱的消费者，请选择查找方式！\n");
    printf("*****选项1 编号查找 ******\n");
    printf("*****选项2 名称查找 ******\n");
    printf("*****选项3 编号加名称查找 ******\n");
    printf("    *****选项4 退出 ******\n");
    scanf("%d",&select);
    if(select==1)
    {   char tmp[15];
        printf("请输入查询编号\n");
        scanf("%s",tmp);
        struct medicine *p=head;
        while(p->next!=NULL)
        {
            struct medicine *q=p->next;
            if(strcmp(q->num,tmp)==0)
             {   flag=1;
                 printf("查询成功！\n");
                 printf("%-8s\t %-8s\t %-8.2f\t\n",q->num,q->name,q->price);
                 break;
             }
             
             p=q;
        }
          
                if(flag==0)
             	printf("查询失败！\n"); 
			 
        
    }
    
    else if(select==2)
    {   char tmp[15];
        printf("请输入查询药品名称\n");
        scanf("%s",tmp);
        struct medicine *p=head;
        while(p->next!=NULL)
        {
            struct medicine *q=p->next;
            if(strcmp(q->name,tmp)==0)
             {   flag=1;
                 printf("查询成功！\n");
                 printf("%-8s\t %-8s\t %-8.2f\t\n",q->num,q->name,q->price);
                 break;
             }
              
             p=q;
        }
        
          
                if(flag==0)
             	printf("查询失败！\n"); 
			 
 
    }

    else if(select==3)
    {   char tmp_num[15],tmp_name[15];
        printf("请输入查询编号和名称\n");
        scanf("%s %s",tmp_num,tmp_name);
        struct medicine *p=head;
        while(p->next!=NULL)
        {
            struct medicine *q=p->next;
            if(strcmp(q->num,tmp_num)==0&&strcmp(q->name,tmp_name)==0)
             {   flag=1;
                 printf("查询成功！\n");
                 printf("%-8s\t %-8s\t %-8.2f\t\n",q->num,q->name,q->price);
                 break;
             }
             
             p=q;
        }
         
                 if(flag==0)
             	printf("查询失败！\n"); 
			 
        

    }
    
    else if(select==4)
    {
       menu_consumer();
    }
    else{
        printf("请输入正确的选择！\n");
        menu_consumer();
    }

    check_good();
 
    
}
void show_all()  //显示药店药品清单 
{   int select=0;
	struct medicine * p=head;
	 printf("请选择排序方法！\n");
	 printf("***1.升序\n");
	 printf("***2.降序\n"); 
	 scanf("%d",&select);
	 if(select==1)
	  { int flag=0;
	  	printf("请输入排序关键字！\n");
	  	printf("***1.编号");
		printf("***2.单价");
		scanf("%d",&flag);
        up_sort(p,flag);
	  }
     else if(select==2)
	  { int flag=0;
	  	printf("请输入排序关键字！\n");
	  	printf("***1.编号");
		printf("***2.单价");
		scanf("%d",&flag);
        down_sort(p,flag);
	  }

     p=p->next;
	printf("编号            名称             单价\n");
    while(p)
    {
        if(strlen(p->num)!=0)
        printf("%-14s\t %-14s\t %-14.2f\t\n",p->num,p->name,p->price);
        p=p->next;
    }
}
void modify()  //修改药品 
{  
   char tmp[20];
   int flag=0;
   int select=0;
   printf("请输入要修改的药品编号(输入0退出)\n");
   scanf("%s",&tmp);
   if(strcmp(tmp,"0")==0)
    {
        return;
    }
    struct medicine *p=head;
        while(p->next!=NULL)
        {
            struct medicine *q=p->next;
            if(strcmp(q->num,tmp)==0)
             {   flag=1;
                 
                  p=q;
                 break;
             }
             
             p=q;
        }

         if(flag==0)
        {
            printf("没有此编号！\n");
            modify();
        }
        else
    {
    printf("请输入要修改的类型！\n");
    printf(" 1.编号\n");
    printf(" 2.名称\n");
    printf(" 3.价格\n");
    scanf("%d",&select);
    FILE*fp;
    fp=fopen("medicine.txt","w+");
    switch(select)
    {
        case 1: 
        {
            char s[20];
            scanf("%s",s);
            strcpy(p->num,s);
            break;
        }
         case 2: 
        {
            char s[20];
            scanf("%s",s);
            strcpy(p->name,s);
            break;
        }
        case 3: 
        {
            double s;
            scanf("%lf",&s);
            if(s<0)
            {
                printf("价格不能为负数！\n");
                break;
            }
            
            p->price=s;
            break;
        }
    }
     p=head->next;
    
     while(p&&p->next)
     {
        
         fprintf(fp,"%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price);
        p=p->next;

     }
    fclose(fp);
    }
    

       


}
void get_pwd(char *buf) //输入密码 
{  memset(buf,0,sizeof(buf));
   int len=0;
   while(1)
	 {
		char c=_getch();
		if(c=='\r')
		{
			break;
		}
		else if(c=='\b')
		 {
		 	printf("\b \b");
             if(len>0)
		 	{    len--;
                 buf[len]='\0';
		 	 
            }
             
		  } 
		  else
		  {
		  	buf[len++]=c;
		  	printf("*");
		  }
}
}
void mod_pwd()  //修改密码 
{  
   char tmppwd[20],tmpzh[20];
   printf("请输入原账号！\n");
   scanf("%s",&tmpzh);
   printf("请输入原密码！\n");
   if(!password(tmpzh)) //密码错误
   {
      printf("警告！！！！\n");
     	 Welcome();
	
   }
   else
   {
          char new1[20],new2[20];
           printf("请输入新密码\n");
           get_pwd(new1);
           printf("请确认新密码\n");
           get_pwd(new2);
           if(strcmp(new1,new2)!=0)
           { 
             printf("两次输入密码不一致！ 请重新输入！\n");
             mod_pwd();

           }
           else 
           {	struct user * p=head_c;
                while(p)
                {
                    if(strcmp(p->zh,tmpzh)==0)
                    {
                        strcpy(p->mm,new1);
                        break;
                    }
                    p=p->next;
                }
                FILE* fp;
                if(id==1)
                {
                    fp=fopen("consumer.txt","w");
                }
                else if(id==2)
                {
                    fp=fopen("manager.txt","w");
                }
               p=head_c->next;
          while(p)
          {  
              fprintf(fp,"%s %s\n",p->zh,p->mm);
              p=p->next;
          }
        
                printf("修改密码成功！\n");
                fclose(fp);
		   }
          
       

   }
}

void init_user() //初始化用户 
{  
    FILE*fp;
    head_c=(struct user *)malloc(sizeof(struct user));
    head_c->next=NULL;
    struct user *q;
    q=head_c;
    q->next=NULL;
    if(id==1)   //判断身份 
    fp=fopen("consumer.txt","r");
    else if(id==2)
    fp=fopen("manager.txt","r");
    if(fp==NULL)
    {
    printf("不能打开此文件！");
    Welcome();
    }
    while(!feof(fp))
    {   struct user *p=(struct user *)malloc(sizeof(struct user));
        fscanf(fp,"%s %s",p->zh,p->mm);
        q->next=p;
        q=p;
    }
    q->next=NULL;
    fclose(fp);
}

void sign_up_user()  //用户注册 
{
    printf("请输入用户名\n");
    char zh[20];
    scanf("%s",zh);
    struct user * p=head_c->next;
    while(p)
    {
        if(strcmp(p->zh,zh)==0)
        {
            printf("已存在用户！\n");
            Welcome();
        }
        p=p->next;
    }
     char new1[20],new2[20];
     memset(new1,0,sizeof(new1));
     memset(new2,0,sizeof(new2));
           printf("请输入密码\n");
           get_pwd(new1);
           fflush(stdin);
           printf("\n");
           printf("请确认新密码\n");
           get_pwd(new2);
           fflush(stdin);
           if(strcmp(new1,new2)!=0)
           {   
		   printf("密码错误！\n");
               Welcome();
           }
           else
       {    struct user * p=head_c;
    while(p->next!=NULL)
    {
        p=p->next;
    }
     struct user *q=(struct user *)malloc(sizeof(struct user));
     q->mm[strlen(q->mm)]='\0';
     q->mm[strlen(q->zh)]='\0';
     strcpy(q->mm,new1);
      strcpy(q->zh,zh);
      p->next=q;
      p=q;

    FILE* fp;
    if(id==1)
    fp=fopen("consumer.txt","a+");
    else if(id==2)
    fp=fopen("manager.txt","a+");
    fprintf(fp,"%-8s\t %-8s\t\n",q->zh,q->mm);
    
    p->next=NULL;
    fclose(fp);
       }


     
}

void login_user()  //用户登录 
{   
    int flag=0;
    printf("请输入账号:\n");
    char zh[20];
    char tm_zh[20],tm_pwd[20];
    scanf("%s",&zh);
    strcpy(tmp_zh,zh);
    FILE*fp;
    if(id==1)
    {   strcpy(now_user,zh);
        fp=fopen("consumer.txt","r");
    }
    else if(id==2)
    {   strcpy(now_manager,zh);
        fp=fopen("manager.txt","r");
    }
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",tm_zh,tm_pwd);
        if(strcmp(zh,tm_zh)==0)
        {   
            flag=1;
        }
    }
    if(flag==0&&id==1)  //用户未注册
    { printf("亲爱的用户现在您尚未有账户，是否注册？ y/n\n");
      getchar();
      char c;
      scanf("%c",&c);
      if(c=='n')
      {
          Welcome();
      }
      else
      { 
        sign_up_user();
      }
      
    }
    else if(flag==0&&id==2)  //管理者未注册
    {   printf("亲爱的管理者现在您尚未有账户，是否注册？ y/n\n");
         getchar();
        char c;
        scanf("%c",&c);
         if(c=='n')
         {
          Welcome();
         }
      else
      { 
        add_manager();
      }
	}
    else //已有账号
    { printf("请输入密码\n");
      if(!password(zh))
      {
          printf("登录失败！\n");
          Welcome();
      }
      else 
      {
          printf("Welcome 用户 :%s\n",zh);
      }
    }

}

void insert_medicine() //插入药品 
{  
   int flag=0;
   struct medicine *p=head;
   char num[20];
   char tmp_num[20],tmp_name[20];
   double tmp_price;
   printf("请输入插入的数据!(输入-1退出)\n");
    scanf("%s",tmp_num);
    
    if(strcmp(tmp_num,"-1")==0)
     {
         return;
     }
   scanf("%s %lf",tmp_name,&tmp_price);
    while(p&&p->next)
   {
       if(strcmp(p->num,tmp_num)==0)
       { printf("此对象已存在！\n");
          return;
       }
       p=p->next;
   }
   printf("请输入想插入的对象编号！(输入 0插入到头部)\n");
   scanf("%s",num);
   p=head;
   
   while(p&&p->next)
   {
       if(strcmp(p->num,num)==0)
       {
           flag=1;
           break;
       }
       p=p->next;
   }
   if(flag==0&&strcmp(num,"0")!=0)
   {
       printf("没有此对象！\n");
       return;
      
   }
   else 
   {
     struct medicine *q=(struct medicine *)malloc(sizeof(struct medicine));
     q->next=NULL;
     strcpy(q->num,tmp_num);
      strcpy(q->name,tmp_name);
      q->price=tmp_price;
      
      if(strcmp(num,"0")==0)
       {  
          q->next=head->next;
          head->next=q;

       }
       else
      {  
      q->next=p->next;
      p->next=q;
      }
   }
      FILE* fp;
      fp=fopen("medicine.txt","w");
       
      p=head->next;
      while(p&&p->next)
      {  
          fprintf(fp,"%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price);
          p=p->next;
      }
      fclose(fp);

   

}

void dlete_medicine() //删除药品 
{   
    char num[20];
    char yao[20];
    int flag=0;
    printf("请输入想删除的编号(输入0退出)\n");
    scanf("%s",num);
    if(strcmp(num,"0")==0)
     {
         return;
     }
    struct medicine *p=head->next;
    struct medicine *tmp=NULL; 
    while(p)
    {
        if(strcmp(p->num,num)==0)
        {   strcpy(yao,p->name);
            flag=1;
            break;
        }
        p=p->next;
    }
    if(flag==0)
    {
        printf("没有此药品！\n");
    }
    else
    {
        struct medicine *q=head;
      
            while(q->next)
            {
                if(strcmp(q->next->num,num)==0)
                {
                    tmp=q->next;
                    q->next=q->next->next;
                    free(tmp);
                    break;
                }
                q=q->next;
            }


     
        FILE*fp;
        fp=fopen("medicine.txt","w+");

        p=head->next;
        while(p&&p->next) //重新写入
        {  fprintf(fp,"%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price);
            p=p->next;
        }
        fclose(fp);
        printf("删除药品%s 成功！\n",yao);

    }
}


void dlete_user() //删除用户 
{  
   char bh[20];
   int flag=0;
   struct user * head_tmp,*q,*p,*tmp;
   head_tmp=(struct user *)malloc(sizeof(struct user));
   head_tmp->next=NULL;
   q=head_tmp;
   FILE *fp;
   fp=fopen("consumer.txt","r");
   while(!feof(fp))
   { struct user*p=(struct user *)malloc(sizeof(struct user));
   	 fscanf(fp,"%s %s",p->zh,p->mm);
   	 q->next=p;
   	 q=p;
   }
   q->next=NULL;
   
   printf("请输入要删除的编号\n");
   scanf("%s",bh);
   p=head_tmp;
   while(p->next)
   {
   	if(strcmp(p->next->zh,bh)==0)
   	 {
   	 	 flag=1;
   	 	 break;
	 }
	 p=p->next;
   }
    
   if(flag==0)
   {
   	printf("没有此用户！\n");
   }
   else if(flag==1)
    {     id=1; //因为是在管理者
        
		
		
		
    	p=head_tmp;
    	while(p->next)
    	{
    		if(strcmp(p->next->zh,bh)==0)
    		 {
    		 	tmp=p->next;
    		 	p->next=p->next->next;
    		 	free(tmp);
    		 	break;
			 }
			 p=p->next;
		}
		 //printf("6666\n");
		FILE*fp;
        fp=fopen("consumer.txt","w+");

        p=head_tmp->next;
        while(p&&p->next)
        {  fprintf(fp,"%-8s\t %-8s\t\n",p->zh,p->mm);
            p=p->next;
        }
        fclose(fp);
	}
	   id=2;
	   p=head_tmp;
       while(p->next)
       {
       	struct user *tmp;
       	tmp=p->next;
       	free(p);
       	p=tmp;
	   }
	  
   
   
   
   
   
}

void purchase() //购买药品 
{   
    char bh[20];
    int cnt[60000];
	 memset(cnt,0,sizeof(cnt)); 
	show_all();
    struct medicine *head_p =(struct medicine *)malloc(sizeof(struct medicine));
    head_p->next=NULL;
    int select=0;
    printf("*************请输入要购买的药品名称!******************\n");
    printf("*** 输入0结束购买！***\n");
    printf("*** 输入1购买！***\n");
    printf("*** 输入-1修改购买清单的某一项！***\n");
    while(scanf("%d",&select)==1&&select!=0)

    {   
        if(select!=1&&select!=-1)
        {   if(select!=0)
            {
            	printf("输入错误！\n");
            	printf("请重新输入选择！\n");
            	continue;
			}
            break;
        }
        printf("请输入要购买/删除的编号！\n");
        scanf("%s",bh);
        int flag=0;
        struct medicine * p=head->next;
         while(p)
        {
            
            if(strcmp(p->num,bh)==0)
             {   flag=1;
                 printf("查询成功！\n");
                 printf("%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price);
                 break;
             }
             
             p=p->next;
        }
        if(flag==0)
        {
            printf("没有此药品！请重新输入！\n");

        }
        else
        {   if(select==1)
            {
              int count=0;
              printf("请输入购买数量！\n");
              scanf("%d",&count);
              
            printf("请确认是否购买？y/n\n"); 
            char c;
            getchar();
            scanf("%c",&c);
            if(c=='y')
            {  if(cnt[atoi(bh)]==0)
			   {
				
               struct medicine *q =(struct medicine *)malloc(sizeof(struct medicine));
               strcpy(q->num,p->num);
               strcpy(q->name,p->name);
               q->price=p->price;
               q->total+=count*q->price;
               struct medicine *r=head_p;
               while(r->next)
               {
               	r=r->next;
			   }
			   r->next=q;
			   q->next=NULL;
		       }
		        cnt[atoi(bh)]+=count;

            }
            }
            else if(select==-1)
            {
                 printf("请确认是否删除？y/n\n");
                 getchar();
                 char c;
                 c=getchar();
                 struct medicine *tmp;
             if(c=='y')
             {  
               struct medicine *q=head_p;
      
                  while(q->next)
               {
                     if(strcmp(q->next->num,bh)==0)
                  {     q->total=0;
                       tmp=q->next;
                       q->next=q->next->next;
                       free(tmp);
                       break;
                  }
                q=q->next;
               }
               cnt[atoi(bh)]=0;
            }


           }

        }
           printf("*************请输入要购买的药品名称!******************\n");
          printf("*** 输入0结束购买！***\n");
         printf("*** 输入1购买！***\n");
        printf("*** 输入-1修改购买清单的某一项！***\n");
    }

      printf("购买如下::\n");
      up_sort(head_p,3);//升序排序
      struct medicine * p=head_p->next;

      double all_price=0; //总共花多少钱
	   while(p)
        { 
        all_price+=p->price*cnt[atoi(p->num)];
        printf("%-8s\t %-8s\t %-8.2f\t\n",p->num,p->name,p->price*cnt[atoi(p->num)]);
        p=p->next;
        }
        printf("%.2f元!\n",all_price);
        printf("请确认是否购买！y/n\n");
        getchar();
        char c;
        c=getchar();
        if(c=='y')
        {    
		    FILE* fp=fopen("money.txt","r");
            struct medicine *head_i=(struct medicine*)malloc(sizeof(struct medicine));
            head_i->next=NULL;
            struct medicine *r;
            r=head_i;
            
            while(!feof(fp))
            {  struct medicine *tmp=(struct medicine *)malloc(sizeof(struct medicine));
               fscanf(fp,"%s %s %lf %d %lf",tmp->num,tmp->name,&tmp->price,&tmp->cnt,&tmp->total);
               tmp->cnt+=cnt[atoi(tmp->num)];
               tmp->total=tmp->cnt*tmp->price;
               r->next=tmp;
               r=tmp;
            }
           
            r->next=NULL;
            fclose(fp);
            fp=fopen("money.txt","w");
            r=head_i->next;
            while(r&&r->next)
            {
                 fprintf(fp,"%-8s\t %-8s\t %.2f\t %d\t %.2f\t\n",r->num,r->name,r->price,r->cnt,r->total);
                 r=r->next;
            }
            fclose(fp);

           
            printf("%.2f元！感谢您的惠顾！\n",all_price);
            r=head_i;
            while(r->next)
             {
             	struct medicine *tmp;
             	tmp=r->next;
             	free(r);
             	r=tmp;
			 }

        }

}

void check_income()  //统计收益 
{  
   int select=0;
   double all_price=0,part_price=0;
   printf("**********请选择统计类型！*************\n");
   printf("***** ****1.统计总收益！*********\n");
   printf("**********2.统计售出数量大于（）\n");
   printf("**********3.统计价格大于（）并且出售总值（）大于（）的商品！***********************\n");
   scanf("%d",&select);
   FILE* fp=fopen("money.txt","r");
            struct medicine *head_i=(struct medicine*)malloc(sizeof(struct medicine));
            head_i->next=NULL;
            struct medicine *r;
            r=head_i;
            while(!feof(fp))
            {  struct medicine *tmp=(struct medicine *)malloc(sizeof(struct medicine));
               fscanf(fp,"%s %s %lf %d %lf",tmp->num,&tmp->name,&tmp->price,&tmp->cnt,&tmp->total);
              
               all_price+=tmp->total;
               r->next=tmp;
               r=tmp;
            }
           
            r->next=NULL;
            fclose(fp);

   if(select==1)
   {
      printf("总收入:\n");
      printf("%.2f元!\n",all_price);
      struct medicine *tmp=head_i;
      up_sort(tmp,3);
      r=tmp->next; 
      printf("编号            名称             单价           数量             总价  \n");
      while(r)
       { if(strlen(r->num)!=0)
        printf("%-8s\t %-8s\t %-8.2f\t %-8d\t %-8.2f\t\n",r->num,r->name,r->price,r->cnt,r->total);
        r=r->next;
        }
   }
   else if(select==2)
   { int cnt=0;
   	printf("请输入售出总数限制\n");
   	scanf("%d",&cnt);
    struct medicine *tmp=head_i;
      up_sort(tmp,3);
      r=tmp->next;  
       while(r)
       {
           if(r->cnt>=cnt)
           {  
               part_price+=r->total;
           }
           r=r->next;
       }
      printf("部分总收入:\n");
      printf("%.2f元!\n",part_price);
      r=head_i->next->next;
       printf("编号            名称             单价           数量             总价  \n");
      while(r)
       {  if(r->cnt>=cnt&&(strlen(r->num)!=0))
        printf("%-8s\t %-8s\t %-8.2f\t %-8d\t %-8.2f\t\n",r->num,r->name,r->price,r->cnt,r->total);
        r=r->next;
        }
   	
   	
	} 
   else if(select==3)
   {   double price=0,total=0;
       printf("请输入单价限制!\n");
       scanf("%lf",&price);
       printf("请输入出售总值限制！\n");
       scanf("%lf",&total);
        struct medicine *tmp=head_i;
        up_sort(tmp,3);
        r=tmp->next; 
       while(r)
       {
           if(r->total>=total&&r->price>=price&&(strlen(r->num)!=0))
           {
               part_price+=r->total;
           }
           r=r->next;
       }
      printf("部分总收入:\n");
      printf("%.2f元!\n",part_price);
      r=head_i->next->next;
       printf("编号            名称             单价           数量             总价  \n");
      while(r)
       { if(r->total>=total&&r->price>=price)
        printf("%-8s\t %-8s\t %-8.2f\t %-8d\t %-8.2f\t\n",r->num,r->name,r->price,r->cnt,r->total);
        r=r->next;
        } 


   }
   
            r=head_i;
            while(r->next)
             {
             	struct medicine *tmp;
             	tmp=r->next;
             	free(r);
             	r=tmp;
			 }


}


void notice()
{   char s[200];
    FILE *fp=fopen("notice.txt","a+");
	printf("请输入你想输入的告示！(输入0退出)\n");
	while(scanf("%s",s)==1&&strcmp(s,"0")!=0)
	{ notice_cnt++;
	  fprintf(fp,"%s\n",s);	
	} 
	fclose(fp);
	

} 
void message()
{   char s[200];
    FILE *fp=fopen("message.txt","a+");
	printf("请输入你想输入的留言！(输入0退出)\n");
	while(scanf("%s",s)==1&&strcmp(s,"0")!=0)
	{ message_cnt++;
	  fprintf(fp,"%s %s\n",tmp_zh,s);	
	} 
	fclose(fp);
	

} 
void show_notice()
{
	FILE*fp=fopen("notice.txt","r");
	while(!feof(fp)&&notice_cnt--)
	{   char s[100];
	    fscanf(fp,"%s",s);
		printf("notice:%s\n",s);
	}
	fclose(fp);
	fp=fopen("notice.txt","w"); //读完清空文件
	fclose(fp);
	notice_cnt=0;
 } 
 void show_message()
{
	FILE*fp=fopen("message.txt","r");
	while(!feof(fp)&&message_cnt--)
	{   char s[100],zh[100];
	    fscanf(fp," %s %s",zh,s);
		printf("message from %s :%s\n",zh,s);
	}
	fclose(fp);
	fp=fopen("message.txt","w"); //读完清空文件
	fclose(fp);
	message_cnt=0; 
 } 

 void add_manager()
 {
 	FILE* fp;
    printf("请输入sudo密码!\n");
    char pwd[20];
	get_pwd(pwd);
	if(strcmp(pwd,sudo)!=0)
	 {
	 	printf("密码错误！\n");
         Welcome();
	  } 
	 else
	{   char zh[20],mm[20];
		FILE*fp;
		fp=fopen("manager.txt","r");
		printf("请输入想添加的管理者！\n");
		scanf("%s",zh);
		while(!feof(fp))
		 {  char zhh[20],mmm[20];
		 	fscanf(fp,"%s %s",zhh,mmm);
		 	if(strcmp(zhh,zh)==0)
		 	{
		 		printf("此管理者已存在！\n");
		 		Welcome();
			 }
		 	
		 }
		 fclose(fp);
		 fp=fopen("manager.txt","a");
		char new1[20],new2[20];
           printf("请输入新密码\n");
           get_pwd(new1);
           printf("请确认新密码\n");
           get_pwd(new2);
           if(strcmp(new1,new2)!=0)
           { //printf("%s | %s\n",new1,new2);
             printf("两次输入密码不一致!\n");
             Welcome();
             
           }
           else
		   {
		   	fprintf(fp,"%s %s\n",zh,new1);
		   	printf("Welcome new manager %s!\n",zh);
			} 
			fclose(fp);
		
	}
    
 } 
 
 
 void dlete_manager() //删除用户 
{  
   char bh[20];
   int flag=0;
   struct user * head_tmp,*q,*p,*tmp;
   printf("请输入sudo 密码！\n");
   char pwd[20];
   get_pwd(pwd);
   if(strcmp(pwd,sudo)!=0)
   { 
   	printf("sudo密码错误！\n");
   	return;
	} 
   head_tmp=(struct user *)malloc(sizeof(struct user));
   head_tmp->next=NULL;
   q=head_tmp;
   FILE *fp;
   fp=fopen("manager.txt","r");
   while(!feof(fp))
   { struct user*p=(struct user *)malloc(sizeof(struct user));
   	 fscanf(fp,"%s %s",p->zh,p->mm);
   	 q->next=p;
   	 q=p;
   }
   q->next=NULL;
   
   printf("请输入要删除的编号\n");
   scanf("%s",bh);
   p=head_tmp;
   while(p->next)
   {
   	if(strcmp(p->next->zh,bh)==0)
   	 {
   	 	 flag=1;
   	 	 break;
	 }
	 p=p->next;
   }
   
    //printf("1111111111111\n");
    
   if(flag==0)
   {
   	printf("没有管理者！\n");
   }
   else if(flag==1)
    {    
        
		
		
		
    	p=head_tmp;
    	while(p->next)
    	{
    		if(strcmp(p->next->zh,bh)==0)
    		 {
    		 	tmp=p->next;
    		 	p->next=p->next->next;
    		 	free(tmp);
    		 	break;
			 }
			 p=p->next;
		}
		//printf("2222222222111111\n");
		FILE*fp;
        fp=fopen("manager.txt","w+");

        p=head_tmp->next;
        while(p)
        {  fprintf(fp,"%-8s\t %-8s\t\n",p->zh,p->mm);
            p=p->next;
        }
        fclose(fp);
        //printf("333333333111111\n");
	}
	   p=head_tmp;
       while(p->next)
       {
       	struct user *tmp;
       	tmp=p->next;
       	free(p);
       	p=tmp;
	   }
	   
       // printf("444444444\n");
   
   
   
   
}
void logout()  //注销用户
{   printf("请三思！ y/n\n");
    char c;
    getchar();
    c=getchar();
    if(c=='n')
    {
        return;

    }
    else 
    { printf("请输入密码！\n");
    if(!password(now_user))
    {
        printf("密码错误！\n");
    }
    else
    {   
      int flag=0;
      struct user * head_tmp,*q,*p,*tmp;
      head_tmp=(struct user *)malloc(sizeof(struct user));
      head_tmp->next=NULL;
      q=head_tmp;
      FILE *fp;
      fp=fopen("consumer.txt","r");
      while(!feof(fp))
      { struct user*p=(struct user *)malloc(sizeof(struct user));
   	    fscanf(fp,"%s %s",p->zh,p->mm);
   	    q->next=p;
   	  q=p;
      }
      q->next=NULL;
      p=head_tmp;
      while(p->next)
     {
   	   if(strcmp(p->next->zh,now_user)==0)
   	   {
   	 	  flag=1;
   	 	  break;
	   }
	   p=p->next;
     }
    	p=head_tmp;
    	while(p->next)
    	{
    		if(strcmp(p->next->zh,now_user)==0)
    		 {
    		 	tmp=p->next;
    		 	p->next=p->next->next;
    		 	free(tmp);
    		 	break;
			 }
			 p=p->next;
		}
		 
        fp=fopen("consumer.txt","w+");

        p=head_tmp->next;
        while(p&&p->next)
        {  fprintf(fp,"%-8s\t %-8s\t\n",p->zh,p->mm);
            p=p->next;
        }
        fclose(fp);
	    
	   p=head_tmp->next;
       while(p)
       {
       	struct user *tmp;
       	tmp=p->next;
       	free(p);
       	p=tmp;
	   }
	   
	   free(head_tmp);
        printf("亲爱的%s 用户，我们有缘再见!\n",now_user);
    }
}
}

void up_sort(struct medicine * L,int flag)
{
	int i ,count = 0, num;//count记录链表结点的个数，num进行内层循环，
	struct medicine  *p, *q, *tail;//创建三个指针，进行冒泡排序
	p = L;
	while(p->next != NULL)//计算出结点的个数
	{
		count++;
		p = p->next;
	}
	for(i = 0; i < count - 1; i++)//外层循环，跟数组冒泡排序一样
	{
		num = count - i - 1;//记录内层循环需要的次数，跟数组冒泡排序一样，
		q = L->next;//令q指向第一个结点
		p = q->next;//令p指向后一个结点
		tail = L;//让tail始终指向q前一个结点，方便交换，也方便与进行下一步操作
		while(num--)//内层循环 次数跟数组冒泡排序一样
		{
			if(flag==1) //按编号
            {
			if(atoi(q->num)>atoi(p->num))
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
            if(flag==2) //按单价
            {
			if(q->price>p->price)
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
            if(flag==3) //按总价
            {
			if(q->total>p->total)
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
			tail = tail->next;
			q = tail->next;
			p = q->next;
		 } 
	} 
}

void down_sort(struct medicine * L,int flag)
{
	int i ,count = 0, num;//count记录链表结点的个数，num进行内层循环，
	struct medicine  *p, *q, *tail;//创建三个指针，进行冒泡排序
	p = L;
	while(p->next != NULL)//计算出结点的个数
	{
		count++;
		p = p->next;
	}
	for(i = 0; i < count - 1; i++)//外层循环，跟数组冒泡排序一样
	{
		num = count - i - 1;//记录内层循环需要的次数，跟数组冒泡排序一样，
		q = L->next;//令q指向第一个结点
		p = q->next;//令p指向后一个结点
		tail = L;//让tail始终指向q前一个结点，方便交换，也方便与进行下一步操作
		while(num--)//内层循环 次数跟数组冒泡排序一样
		{   if(flag==1) //按编号
            {
			if(atoi(q->num)<atoi(p->num))
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
            if(flag==2) //按单价
            {
			if(q->price<p->price)
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
            if(flag==3) //按总价
            {
			if(q->total<p->total)
			{
				q->next = p->next;
				p->next = q;
				tail->next = p;
			}
            }
			tail = tail->next;
			q = tail->next;
			p = q->next;
		 } 
	} 
}