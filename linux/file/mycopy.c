#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


#define SIZE 8192
int main(int argc,char *argv[]){
    char buf[SIZE];
    int fd_src,fd_dest,len;

    if(argc<3){
        printf("./mycopy src dest\n");
        exit(1);
    }

    fd_src=open(argv[1],O_RDONLY);
    fd_dest=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0644);
    
    while(len=read(fd_src,buf,sizeof(buf))>0){
        write(fd_dest,buf,len);
    }

    //read读失败返回-1，读到文件末尾返回0
    //成共返回读到的字节数

    close(fd_src);
    close(fd_dest);

    return 0;
}
