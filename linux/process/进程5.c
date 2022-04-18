#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int fd[2];
    pid_t pid;
    char str[1024]="hello itcast";
    char buf[1024];

    //fd[0] 读端
    //fd[1] 写端
    if(pipe(fd)<0){
        perror("pipe");
        exit(1);
    }
    pid=fork();
    //父写子读
    if(pid>0){
        //关闭父读
        close(fd[0]);

        sleep(2);
        write(fd[1],str,strlen(str));
        wait(NULL);
    }else if(pid==0){
        int len;
        //子进程关闭写端
        close(fd[1]);
        len=read(fd[0],buf,sizeof(buf));
        //读时共享，写时复制 可以直接读str
//        sprintf(str,"child %s",buf);
        write(STDOUT_FILENO,buf,len);
    }
    else{
        perror("fork");
        exit(1);
    }
    return 0;
}
