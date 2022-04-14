#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<dirent.h>
#include<signal.h>

#define normal       0   //正常
#define out_redirect 1   //输出重定向
#define in_redirect  2   //输入重定向
#define have_pipe    3   //有管道
#define out_redirect_acc  4 //累加输出重定向
char arglist[100][256];

void print_promt();
void get_input(char **buf);
void explain_input(char *,int *,char a[100][256]);
void do_cmd(int , char a[100][256]);
int find_command(char *);

int background=0;  //判断是否存在后台运行符

void handler(int signo)
{
    char tmp[256];
    char tmpa[256];
    int tt=0;
    getcwd(tmp,256);
    int dd=strlen(tmp)-2;      //这段代码是提取出路径中的最后一个文件
    for(int i=dd;i>=0;i--)
    {
        if(tmp[i]=='/')
        {
            tt=i;
            break;
        }
    }
    for(int i=tt;i<=dd+1;i++) tmpa[i-tt]=tmp[i];
    tmpa[dd+2-tt]='\0'; 
    printf("\001\033[1m\002");
    printf("\033[34m");
    printf("\n错误!my_shell@%s$$:",tmp);
    printf("\001\033[0m\002");
    //setbuf(stdout,_IO_BUFSIZ);
}

void ShowHistory()
{
    int i = 0;
    HIST_ENTRY ** his;
    his = history_list();
    while(his[i] != NULL)
    printf("%s\n", his[i++]->line);
}

int my_cd(char *buf)
{
    if(chdir(buf)<0)
    return 0;
    else return 1;
}

int main(int argc,char **argv)
{
    system("clear");
    setbuf(stdout,NULL);       /*程序在接受到SIGINT信号时转入的
    处理函数不处理缓冲区会转入下一行 可以删除掉看看*/
    read_history(NULL);    //默认在~/.history
    int i=0;
    int argcount=0;
    char **arg=NULL;
    signal(SIGINT,handler);
    while(1){
        char *buf=(char*)malloc(256);
        if(buf==NULL)
        {
            perror("error in malloc\n");
            exit(1);
        }
        background=0;
        memset(buf,0,256);
        print_promt();
        get_input(&buf);
        if(!strcmp(buf,"exit") || !strcmp(buf,"logout")) break;
        for(i=0;i<100;i++) arglist[i][0]='\0';
        argcount=0;
        explain_input(buf,&argcount,arglist);
        if(!strcmp(buf,"history"))
        {
            ShowHistory();
            continue;
        }
/*         for(int i=0;i<argcount;i++)
        printf("%s\n",arglist[i]); */
        if(!strcmp(arglist[0],"cd"))
        {
            arglist[1][strlen(arglist[1])]='\0';
            if(my_cd(arglist[1]))
            {
                char tmp_file[256];
                getcwd(tmp_file,256);
                continue;
            }
            else
            {
                printf("param error!\n");
                continue;
            }
        }
        do_cmd(argcount,arglist);    
        free(buf);
    }
    exit(0);
}

void print_promt()
{
    setbuf(stdout,NULL);
    char tmp[256];
    char tmpa[256];
    int tt=0;
    getcwd(tmp,256);
    int dd=strlen(tmp)-2;
    for(int i=dd;i>=0;i--)
    {
        if(tmp[i]=='/')
        {
            tt=i;
            break;
        }
    }
    for(int i=tt;i<=dd+1;i++) tmpa[i-tt]=tmp[i];
    tmpa[dd+2]='\0';
    printf("\001\033[1m\002");
    printf("\033[34m");
    printf("\nmy_shell@%s$$:",tmpa);
    printf("\001\033[0m\002");
    //setbuf(stdout,_IO_BUFSIZ);
}

void get_input(char **buf)
{
    int len=0;
    char ch='\0';
/*     ch=getchar();
    while(len<256)
    {
        if(ch=='\n') break;
        buf[len++]=ch;
        ch=getchar();
    } */
    *buf=readline("my_shell@"); //不在这里加字符串可能会出现缓冲区问题 导致光标移动异常
    add_history(*buf);
    write_history(NULL);
    if(len==256)

    {
        perror("command is too long \n");
        return 0;
    }
}

void explain_input(char *buf,int *argcount,char arglist[100][256])
{
    char *q=buf;
    char *p=buf;
    int number=0;
    for(int i=0;i<strlen(buf);i++)
    if(buf[i]=='#')
    {
        background=1;  //判断是否存在后台运行符
    }
    while(1)
    {
        if(p[0]=='\0')
        break;
        if(p[0]==' ')
        p++;
        else
        {
            q=p;
            number=0;
            while(q[0]!='\0' && q[0]!=' '){
                q++;
                number++;
            }
            strncpy(arglist[*argcount],p,number+1);
            arglist[*argcount][number]='\0';//最后一项为'\0'
            *argcount=*argcount+1;
            p=q;
        }
    }
}

void do_cmd(int argcount,char arglist[100][256])
{
    int flag=0;
    int how=0;     //检测是否存在重定向 管道
    int status=0;
    int i=0;
    int fd=0;
    char *arg[argcount+1];
    char *argnext[argcount+1];
    char *file;
    pid_t pid=0;

    for(i=0;i<argcount;i++)
    {
        arg[i]=(char*)arglist[i];
    }
    arg[argcount]=NULL;
    for(i=0;arg[i]!=NULL;i++)
    {
        if(!strcmp(arg[i],">"))
        {
            flag++;
            how=out_redirect;
            if(arg[i+1]==NULL)
            flag++;     //错误的格式
        }
    }
    for(i=0;arg[i]!=NULL;i++)
    {
        if(!strcmp(arg[i],">>"))
        {
            flag++;
            how=out_redirect_acc;
            if(arg[i+1]==NULL)
            flag++;     //错误的格式
        }
    }
    for(i=0;arg[i]!=NULL;i++)
    {
        if(!strcmp(arg[i],"<"))
        {
            flag++;
            how=in_redirect;
            if(i==0)
            flag++;     //错误的格式
        }
    }  
    for(i=0;arg[i]!=NULL;i++)
    {
        if(!strcmp(arg[i],"|"))
        {
            flag++;
            how=have_pipe;
            if(arg[i+1]==NULL)
            flag++;     //错误的格式
            if(i==0)
            flag++;
        }
    } 
    if(flag>1)
    {
        perror("wrong command!\n");
        return;
    }
    if(how==out_redirect)
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],">")==0)
            {
                file=arg[i+1];
                arg[i]=NULL;
            }
        }
    }
    if(how==in_redirect)
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"<")==0)
            {
                file=arg[i+1];
                arg[i]=NULL;
            }
        }
    }
    if(how==have_pipe)
    {
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"|")==0)
            {
                arg[i]=NULL;
                int j;
                for(j=i+1;arg[j]!=NULL;j++)
                {
                    argnext[j-i-1]=arg[j];
                }
                argnext[j-i-1]=arg[j]; //其实就是NULL
                break;
            }
        }
    }
    if((pid=fork())<0)
    {
        printf("fork error\n");
        return;
    }
    switch (how)
    {
        case 0:     //没有什么参数
            if(pid==0)
            {
                if(!find_command(arg[0]))
                {
                    perror("can't find this command!\n");
                    exit(0);
                }
                execvp(arg[0],arg);   //子进程运行参数命令
                exit(0);              //退出子进程
            }
            break;
        case 1:    //输出重定向
            if(pid==0)
            {
                if(!find_command(arg[0]))
                {
                    perror("can't find this command!\n");
                    exit(0);
                }
                fd=open(file,O_RDWR|O_CREAT|O_TRUNC,0644); //输出重定向的目标文件有可能不存在
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 2:    //输入重定向
            if(pid==0)
            {
                if(!find_command(arg[0]))
                {
                    printf("%s :Command can not found\n",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDONLY);
                dup2(fd,0);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 3:
            if(pid==0)
            {
                int pid2=0;
                int fd2=0;
                int status=0;
                if((pid2=fork())<0)   //子进程再次分离一个子进程
                {
                    perror("error in fork\n");
                    exit(0);
                }
                else if(pid2==0)  //子进程
                {
                    if(!find_command(arg[0]))
                    {
                        printf("%s :Command can not found\n",arg[0]);
                        exit(1);
                    }
                    fd2=open("/tmp/youdontnofile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                    dup2(fd2,1);
                    execvp(arg[0],arg);
                    exit(0);
                }
                if(waitpid(pid2,&status,0)==-1)  //第三个参数未被设置 所以阻塞父进程
                {
                    printf("wait child process error\n");
                    exit(1);
                }
                if(!find_command(argnext[0]))
                {
                    printf("%s :Command can not found\n",argnext[0]);
                    exit(1);
                }
                fd2=open("/tmp/youdontnofile",O_RDONLY);
                dup2(fd2,0);
                execvp(argnext[0],argnext);
                if(remove("/tmp/youdontnofile"))
                {
                    perror("error in remove\n");
                }
                exit(1);
            }
            break;
        case 4:       
            if(pid==0)
                {
                    if(!find_command(arg[0]))
                    {
                        perror("can't find this command!\n");
                        exit(0);
                    }
                    fd=open(file,O_RDWR|O_APPEND,0644); 
                    dup2(fd,1);
                    execvp(arg[0],arg);
                    exit(0);
                }
                break;
        default:
            break;
    }
    if(background==1)  //子进程不会走到这里来
    {
        return; //父进程直接返回
    }
    if(waitpid(pid,&status,0)<0)
    {
        perror("error in wairpid\n");
        exit(1);
    }
}

int find_command(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char *path[]={"./","/bin","/usr/bin","/home/lizhaolong/suanfa/TeamF/LZL/Requirement",NULL};
    //为了执行一些自己写的命令 所以加上了工作路径
    if(strncmp(command,"./",2)==0)
    {
        command=command+2;//指针向后移动
    }
    int i=0;
    while(path[i]!=NULL){
        if((dp=opendir(path[i]))==NULL)
        {
            perror("error in opendir\n");
            exit(1);
        }
        while((dirp=readdir(dp))!=NULL){
            if(!strcmp(dirp->d_name,command))
            {
                //printf("找到！\n");
                close(dp);
                return 1;
            }
        }
        close(dp);
        i++;
    }
    return 0;
}
