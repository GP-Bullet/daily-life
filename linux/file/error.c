#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
int main(){
    int fd=open("abc",O_WRONLY);
    if(fd<0){
//        printf("errno=%d\n",errno);
        printf("我靠open出错了 %s\n",strerror(errno));
//        perror("我靠open出错了");
    }
    printf("fd=%d\n",fd);
    return 0;
}