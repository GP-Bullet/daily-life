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
    struct sockaddr_in severaddr;
    int confd;
    int len;
    char ipstr[]="192.168.123.4";
    char buf[MAXLEN];
    if(argc<2){
        printf("./client str\n");
        exit(1);
    }
    //1.创建一个socket
    confd=socket(AF_INET,SOCK_STREAM,0);
    //2.connect前知道自己服务器的ip和端口号
        //初始化服务器地址
    bzero(&severaddr,sizeof(severaddr));
    severaddr.sin_family=AF_INET;
    inet_pton(AF_INET,ipstr,&severaddr.sin_addr.s_addr);//ip地址转换
    severaddr.sin_port=htons(SERVER_PORT);

    //3.链接服务器
    //没有调bind，分配一个随机的端口号使用
    connect(confd,(struct sockaddr*)&severaddr,sizeof(severaddr));//fd，地址记得强转，结构体长度

    //4.请求服务器处理数据
    write(confd,argv[1],strlen(argv[1]));
    //len=read(confd,buf,sizeof(buf));
    //write(STDOUT_FILENO,buf,len);

    //5.关闭socket
    close(confd);

    return 0;
}