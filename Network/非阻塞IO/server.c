#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
 
 
int main(int argc, char* argv[]){
 
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("create socket failed!, errno=%d\n",errno);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8008);
 
    int ret;
    ret = bind(fd, (struct sockaddr*) &addr, sizeof(addr));
    if(ret == -1){
        printf("bind failed!, errno=%d",errno);
        close(fd);
    }
    ret = listen(fd, SOMAXCONN);
    if(ret == -1){
        printf("listen failed!, errno=%d",errno);
    }
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);
    int afd = accept(fd, (struct sockaddr*) &clientaddr, &clientaddrlen);
    if(afd != -1){
        printf("A client connected!,ip=%s,port=%d\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
        char buf[256] = {0};
        sleep(5);
        ret = recv(afd, buf, 256, 0);
        if(ret > 0){
            printf("recv %d byte:%s\n",ret,buf);
        }
        else if(ret == -1){
            printf("recv error!,errno=%d\n",errno);
        }
        else{
            printf("client disconnect!\n");
        }
    }
    else{
        printf("accept failed!,errno=%d\n",errno);
    }
}