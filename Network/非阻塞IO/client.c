#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include<errno.h>
#include<string.h>
#include <fcntl.h>
 
int main(int argc, char* argv[]){
 
 
    if(argc != 3){
        printf("please input IP port\n");
    }
    char* ip = argv[1];
    unsigned int port = atoi(argv[2]);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("create socket failed!, errno=%d\n",errno);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
 
    int ret;
    ret = connect(fd, (struct sockaddr*) &addr, sizeof(addr));
    if(ret == -1){
        printf("connect failed!, errno=%d",errno);
    }
    else{
        //连接成功后将fd设置为非阻塞
        int flags = fcntl(fd, F_GETFL);
        flags |= O_NONBLOCK;
        ret = fcntl(fd, F_SETFL, flags);
        if(ret == -1){
            printf("set O_NONBLOCK failed!,errno=%d\n",errno);
        }
        char *buf = "hello, I am a client!";
        int cnt = 0;
        while(1){
            ret = send(fd, buf, strlen(buf), 0);
            if(ret > 0){
                cnt++;
                printf("send %d byte:%s,cnt = %d\n",ret,buf,cnt);
            }
            else if(ret == -1){
                if(errno == EAGAIN){
                    printf("send try again\n");
                    sleep(1);
                    continue;
                }
                else
                    printf("send error!,errno=%d\n",errno);
            }
            else{
                printf("server disconnect!\n");
            }
        }
 
    }
 
}