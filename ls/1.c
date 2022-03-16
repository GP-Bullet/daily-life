#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<sys/stat.h>
#include<limits.h>

#define MAXROWLEN 80                           //一行显示的最多字符数


void error(char *p,int line)                //错误处理函数
{
    printf("error !:%d",line);
    perror(p);
    exit(1);
}

void take_out(char *path,char *name)    //从路径名中解析出文件名
{
    int i,j;
    for(i=0,j=0;i<strlen(path);i++)
    {
        if(path[i] == '/')
        {
            j=0;
            continue;
        }
        name[j++]=path[i];
    }
    name[j]='\0';
}

void display_attribute(struct stat buf,char *name)          //获取文件属性并打印(-l)
{
    char buf_time[32];
    char name_attribute[11];
    for(int i=0;i<10;i++)
    {
        name_attribute[i]='-';
    }
    name_attribute[10]='\0';


    struct passwd *psd;         //存放用户名
    struct group *grp;          //存放组名

    //获取文件类型
    if(S_ISLNK(buf.st_mode))
    name_attribute[0]='l';
    else if(S_ISREG(buf.st_mode))
    name_attribute[0]='-';
    else if(S_ISDIR(buf.st_mode))
    name_attribute[0]='d';
    else if(S_ISCHR(buf.st_mode))
    name_attribute[0]='c';
    else if(S_ISBLK(buf.st_mode))
    name_attribute[0]='b';
    else if(S_ISFIFO(buf.st_mode))
    name_attribute[0]='f';
    else if(S_ISSOCK(buf.st_mode))
    name_attribute[0]='s';

    //获取用户权限
    if(buf.st_mode & S_IRUSR)
    name_attribute[1]='r';
    if(buf.st_mode & S_IWUSR)
    name_attribute[2]='w';
    if(buf.st_mode & S_IXUSR)
    name_attribute[3]='x';

    //获取用户组权限
    if(buf.st_mode & S_IRGRP)
    name_attribute[4]='r';
    if(buf.st_mode & S_IWGRP)
    name_attribute[5]='w';
    if(buf.st_mode & S_IXGRP)
    name_attribute[6]='x';
    if(buf.st_mode & S_IROTH)

    //获取其他权限
    name_attribute[7]='r';
    if(buf.st_mode & S_IWOTH)
    name_attribute[8]='w';
    if(buf.st_mode & S_IXOTH)
    name_attribute[9]='x';

    //打印
    printf("%s ",name_attribute);
    printf("%d ",(int)buf.st_nlink);       //打印连接数

    //得到用户名与用户组名
    psd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_gid);
    printf("%s %s ",psd->pw_name,grp->gr_name);
    printf("%-d ",(int)buf.st_size);         //打印文件大小

    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1]='\0';      //去掉换行符
    printf("    %-s",buf_time);                 //打印文件时间信息
}


/*
 *根据命令行参数和完整路径名显示目标文件
 *参数flag：命令参数
 *参数pathname;包含了文件名的路径名
 */

 void display(int flag,char *pathname)
{

     void display_R(int flag,char *path);
    int i,j;
    struct stat buf;
    char name[260];

     //用lstat 因为它牛，多个l，可以解析链接文件
    if(lstat(pathname,&buf)==-1)
    {
        error("display",__LINE__);
    }

    take_out(pathname,name);




    switch(flag)
    {
         case 1:             //没有-a -l -R参数
        if(name[0] !='.')
        {
            printf("%-6s  ",name);
        }                 
        break;
         case 3:          //-a参数，显示包括隐藏文件在内的所有文件
        {
            printf("%-6s  ",name);
        }  
        break;
         case 5:        //-l参数
        {
            if(name[0]!='.')
            {
                display_attribute(buf,name);
                printf(" %s\n",name);
            }
            break;
        }
         case 7:        //同时有-a -l参数
         {
             display_attribute(buf,name);
             printf("  %-s\n",name);
         }
         break;
         case 9:   //-R
         {
             display_R(flag,pathname);
             break;
         }
        case 11:  //-aR
         {
             printf(".  ..\n");
             display_R(flag,pathname);
             break;
         }
         case 13: //-lR
         {
            display_attribute(buf,name);
             printf(" ");
             display_R(flag,pathname);
         }
         case 15: //-alR 
         {
             display_attribute(buf,".");
             printf("  .\n");
             display_attribute(buf,"..");
             printf("  ..\n");
            display_R(flag,pathname);
             break;
         }

     }
 }

void display_R(int flag,char *path)             //-R参数
{

    struct stat buf;
    struct stat buff;
    DIR *dir;
    struct dirent *ptr;
    char allname[256][260],name[256][260],a[260],b[260];
    int i,j,k,len,count;

    if(lstat(path,&buf) == -1)
    {
        if(errno==13)
        {
            return ;
        }
        else
        {
            printf("error di:  %s\n",path); //
            //error("display_R",__LINE__);
            return ;
        }
    }


    if(S_ISDIR(buf.st_mode))    //为一个目录，还有文件或子目录
    {
        printf("\n%s\n",path);  //打印目录名
        count=0;
        dir = opendir(path);
        if(dir == NULL)
        {
            error("display_R",__LINE__);
        }

        i=0;
        while((ptr = readdir(dir))!=NULL)  //获取子目录下的文件 目录名，并连接成绝对路径名
        {
            len=0;
            count++;
            strncpy(allname[i],path,strlen(path));
            allname[i][strlen(path)]='/';
            allname[i][strlen(path)+1]='\0';
            strncat(allname[i],ptr->d_name,strlen(ptr->d_name));
            allname[i][strlen(allname[i])]='\0';

            i++;
        }

        for(i=0;i<count;i++)
            take_out(allname[i],name[i]);

        for(i=0;i<count;i++)
        {
            if(name[i][0] != '.')
            {

                if(lstat(allname[i],&buff) == -1)
                {
                    printf("error242");
                }
                if(S_ISDIR(buff.st_mode))
                   {
                       char *m=(char *)malloc(strlen(allname[i])*sizeof(char));
                        display_R(flag,m);
                        free(m);
                   }

                else
                {
                    if(flag > 11)
                    {
                        display_attribute(buff,allname[i]);
                    }
                    printf("  %s\n",name[i]);
                }
            }
            else
            {
                printf("\n");
                continue;
            }
        }

    }
    else 
    {
        take_out(path,a);

        if(a[0] != '.')
        {
            if(flag > 11)
            {
                display_attribute(buff,allname[i]);
            }
            printf("  %-s\n",a);
        }
    }
}



void display_dir(int flag_param,char *path)             
{

    void take_out(char *path,char *name); //
    DIR *dir;
    struct dirent *ptr;
    int count=0;
    char filename[256][260],fullname[256][260],name[256][260];
    char temp[PATH_MAX];

    //获取该目录下文件总数
    dir=opendir(path);
    if(dir==NULL)
    {
        error("oprndir",__LINE__);
    }

    int i = 0,j,k,len;
    while((ptr = readdir(dir))!=NULL)
    {
        len=0;
        count++;
       // memset(filename[i], 0, strlen(filename[i]));
       //memcpy(filename[i], ptr->d_name,sizeof(ptr->d_name));
        strcpy(filename[i],ptr->d_name);
        len = strlen(ptr->d_name);
        filename[i][len]='\0';
        i++;
    }
    closedir(dir);

    if(count>256)
    {
        error("opendir",__LINE__);
    }



    //按字典序排序
    for(i = 0;i<count-1;i++)
        for(j = 0;j<count-1;j++)
        {
            if(strcmp(filename[j],filename[j+1])>0)
            {
                strcpy(temp,filename[j]);
                strcpy(filename[j],filename[j+1]);
                strcpy(filename[j+1],temp);
            }
        }
        for(i=0;i<count;i++)
        {
            strncat(fullname[i],path,strlen(path));
            fullname[i][strlen(path)]='/';
            fullname[i][strlen(path)+1]='\0';
            strncat(fullname[i],filename[i],strlen(filename[i]));
            fullname[i][strlen(fullname[i])]='\0';

        }

        for(i=0;i<count;i++)
        {
            take_out(fullname[i],name[i]);
        }


        for(i=0;i<count;i++)
        {
            if(flag_param == 9 || flag_param == 11 || flag_param == 15 || flag_param == 13)
            {
                    int flag=1;
                    if(name[i][0] == '.')
                    {
                        flag=0;
                    }
                    if(flag == 1)
                    {
                        display(flag_param,fullname[i]);
                    }
            }   
            else
            display(flag_param,fullname[i]);
            printf("\n");
        }
}


int main(int argc,char **argv)
{
    struct stat buf;
    int i,j,k;
    char path[260];                 //保存路径名
    char param[32];                 //保存命令行参数,目标文件名和目录名不在此数组
    int flag_param=1;            //参数种类,即是否有-l  -a -R选项


    //解析命令行参数,分析-l -a -al -la(真正ls 参数顺序无影响，只是我们要让程序知道)
    j=0;
    for(i=1;i<argc;i++)
    {
        if(argv[i][0]=='-')
        {
            for(k=1;k<strlen(argv[i]);k++,j++)
            {
                param[j]=argv[i][k]; //获取-后面的参数保存到数组param中
            }
        }
    }

   //只支持参数a l R如果有其他选项就报错
    for(i=0;i<j;i++)
    {
        if(param[i] == 'a')
        flag_param+=2;
        else if(param[i] == 'l')
        {
            flag_param+=4;
        }
        else if(param[i] =='R')
        {
            flag_param+=8;
        }
        if(param[i] != 'a' && param[i] != 'l' && param[i] != 'R')        //补-R
        {
            printf("我的ls无该功能");
            exit(1);
        }
    }
    param[j]='\0';


    if(argc==1)
    {
        strcpy(path, ".");
        display_dir(flag_param,path);
        return 0;
    }
    else if(argc==2)
    {
        if(flag_param==1)
        {
            strcpy(path,argv[1]);
        }
        else
        {
            strcpy(path,".");
        }
    }
    else if(argc==3)
    {
        strcpy(path,argv[2]);
    }



    //如果目标文件或目录不存在，报错并退出程序
    if(stat(path,&buf)==-1)
    {
        error("it does not exist",__LINE__);
    }

    if(S_ISDIR(buf.st_mode))        //是一个目录
    {
        display_dir(flag_param,path);
    }
    else                            //是一个文件
    {
        display(flag_param,path);
    }

    return 0;
}




