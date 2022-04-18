#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

void sys_err(char *str,int exitno){
    perror(str);
    exit(exitno);
}

int  main(int argc,char *argv[]){
    char buf[256]="hello nihao\n";
    int fd;
    if(argc<2){
        printf("./a.out fifoname\n");
        exit(1);
    }
   // fd=open(argv[1],O_RDONLY);
    fd=open(argv[1],O_WRONLY);
    if(fd<0){
        sys_err("open",1);
    }
    //向管道里写
    write(fd,buf,strlen(buf));//strlen
    close(fd);
    return 0;
}