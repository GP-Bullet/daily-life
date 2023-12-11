#include<sys/ioctl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>


int main(){
    struct winsize size;//终端窗口大小
    if(isatty(STDOUT_FILENO)==0){
        exit(1);
    }
    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&size)<0){
        perror("ioctl TIOCGWINSZ error");
        exit(1);
    }
    printf("%d rows, %d columns\n",size.ws_row,size.ws_col);
    return 0;
}