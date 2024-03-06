#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    char buf[1024];
    int len;

    len=read(STDIN_FILENO,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,len);

    return 0;
}