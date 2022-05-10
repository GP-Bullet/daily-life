//
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>//bzero
#include<arpa/inet.h>//inet_ntop
#include<sys/types.h>//fd
#include<unistd.h>
#include<ctype.h>


#define SERVER_PORT 8000
#define MAXLINE 4096
int main(){
    struct sockaddr_in severaddr,clientaddr;//
    int sockfd,addrlen,confd;
    int len,i;
    char ipstr[128];

    char buf[MAXLINE];
    //1.socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);  //IPv4 TCP
    //2.bind

    //先初始化地址
    bzero(&severaddr,sizeof(severaddr));//清空
    //地址族协议IPv4
    severaddr.sin_family=AF_INET;
    //IP地址                     //转成网络字节序
    severaddr.sin_addr.s_addr=htonl(INADDR_ANY);//任意IP
    //32位存储空间  "117.32.216.31"
    //端口
    severaddr.sin_port=htons(SERVER_PORT);

    bind(sockfd,(struct sockaddr *)&severaddr,sizeof(severaddr));
    //3.listen
    listen(sockfd,128);
    
    while(1){//从这里循环相应客户端

        
        //4.accept阻塞监听客户端
        addrlen=sizeof(clientaddr);
        confd=accept(sockfd,(struct sockaddr *)&clientaddr,&addrlen);//传出客户端地址  传入传出
        //成功返回一个新的fd  得到客户端信息
        //输出客户端IP地址和端口号
        //
        inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr));//af协议,src,提供数组,str_len
        //返回char*

        printf("client ip %s\tport %d\n",
            inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),
            ntohs(clientaddr.sin_port));//接受到整型转成字符串      网络字节序转主机序
        
        //交换数据用confd
        //5、处理客户端请求
        //转成大写回送
        
        len =read(confd,buf,sizeof(buf));//返回读到字节长度
        i=0;
        while(i<len){
            buf[i]=toupper(buf[i]);//转大写一次一个字符

            i++;
        }
        write(confd,buf,len);


        close(confd);
    }
    close(sockfd);
    return 0;
}