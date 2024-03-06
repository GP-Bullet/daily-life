#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
    int fd;
    if(argc!=2){
        fputs("usage:wrapper file",stderr);
        exit(1);
    }
    fd=open(argv[1],O_RDONLY);
    if(fd<0){
        perror("open");
        exit(1);
    }
    dup2(fd,STDIN_FILENO);//将文件输入到shell
    close(fd);
    execl("./upper","upper",NULL);//参数是占位符
    perror("exec ./upper");
    exit(1);
}
