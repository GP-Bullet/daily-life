#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdlib.h>

int main(void){
    int fd,len;
    int *p;
    fd=open("../hello",O_RDWR);
    if(fd<0){
        perror("open");
        exit(1);
    }

    len=lseek(fd,0,SEEK_END);//计算长度
    //fstat

    p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("mmap");
        exit(1);
    }
//用的是MAP_SHARED，把内存改了，磁盘文件也会跟着改
    close(fd);
    p[0]=0x30313233;//如果成功,p[0]即索引前四个字节
                    //p指向内存的首地址
                    //对应字符0123

    munmap(p,len);

    return 0;
}