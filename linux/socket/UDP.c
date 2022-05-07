//
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#include<ctype.h>
#define MAXLINE 1500
#define SERVER_PORT 8000

int main(){
    int sockfd,i;
    ssize_t len;
    struct sockaddr_in serveraddr,clientaddr;
    char buf[MAXLINE];
    char ipstr[INET_ADDRSTRLEN];//专门的宏16
    socklen_t clientlen;
    //1.用于UDP通信的套接字
    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    //2.初始化地址
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;//IPv4
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);//本地任意IP
    serveraddr.sin_port=htons(SERVER_PORT);
    bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    //3.recvfrom  接受
    //一定要初始化
    while(1){
    clientlen=sizeof(clientaddr);
    //?这里的buf的用途  接受客户端的内容
    len=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&clientaddr,&clientlen);//socklen_t len  传入传出参数
                                                                                //描述结构体大小  
                                                                                //接收到32位 且为大端序
    //返回sszie_t， 有符号类型
    printf("client IP %s\tPORT%d\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr))
            ,ntohs(clientaddr.sin_port));

    i=0;
        while(i<len){
            buf[i]=toupper(buf[i]);//转大写一次一个字符
            i++;
        }
        buf[i]='\0';
    //自己重建一条socket   用原来的socket
    sendto(sockfd,buf,len,0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));//

    }
    close(sockfd);
    return 0;
}