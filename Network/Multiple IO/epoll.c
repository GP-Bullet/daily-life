#include<stdio.h>//系统默认上限
#include<sys/epoll.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>


#define MAXLINE 80
#define SERV_PORT 8000
#define OPEN_MAX 1024

int main(int argc,char *argv[])
{
    int i,j,maxi,listenfd,connfd,sockfd;
    int nready,efd,res;
    ssize_t n;
    char buf[MAXLINE],str[INET_ADDRSTRLEN];    //
    socklen_t clilen;                //
    int client[OPEN_MAX];           //客户端
    struct sockaddr_in cliaddr,servaddr; //addr
    struct epoll_event tep,ep[OPEN_MAX];

    listenfd=Socket(AF_INET,SOCK_STREAM,0);

    bzero(&serva)

}