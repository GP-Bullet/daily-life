#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
int main(void){
    int fd=open("abc",O_RDWR);
    if(fd<0){
        perror("open abc");
        exit(-1);
    }
    lseek(fd,0x1000,SEEK_SET);//4096bytes

    write(fd,"a",1);
    close(fd);

    fd=open("hello",O_RDWR);
    if(fd<0){
        perror("open hello");
        exit(-1);
    }
    printf("hello size= %ld\n",lseek(fd,0,SEEK_END)); //偏移量为0，SEEK_END

    close(fd);



    return 0;
}
