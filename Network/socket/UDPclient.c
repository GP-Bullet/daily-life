#include<netinet/in.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>

#include<fcntl.h>
#define SERVER_PORT 8000
#define MAXLEN 4096
int main(int argc,char **argv){
    struct sockaddr_in serveraddr;
    int confd;

    ssize_t len;
    char ipstr[]="192.168.30.144";
    char buf[MAXLEN];
    if(argc<2){
        printf("./client str\n");
        exit(1);
    }
    //1.创建一个socket
    confd=socket(AF_INET,SOCK_DGRAM,0);
    //2.知道自己服务器的ip和端口号
        //初始化服务器地址
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    inet_pton(AF_INET,ipstr,&serveraddr.sin_addr.s_addr);//ip地址转换
    serveraddr.sin_port=htons(SERVER_PORT);



    //请求服务器处理数据
    sendto(confd,argv[1],strlen(argv[1]),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    
    len=recvfrom(confd,buf,sizeof(buf),0,NULL,0);
    write(STDOUT_FILENO,buf,len);
    //5.关闭socket
    close(confd);

    return 0;
}