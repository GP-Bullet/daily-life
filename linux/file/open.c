#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
//一个open要 三个头文件
#include<stdlib.h>
#include<string.h>

#include<unistd.h>//unix标准头文件
//close

int main(int argc,char *argv[]){
    if(argc<2){
        printf("please ./app + filename");
        exit(1);
    }
    int fd;
    char buf[]="helloworld";
    fd=open(argv[1],O_CREAT|O_RDWR,0777);


    write(fd,buf,strlen(buf));  //sizeof  strlen
    printf("fd=%d\n",fd);

    close(fd);
    return 0;
}



