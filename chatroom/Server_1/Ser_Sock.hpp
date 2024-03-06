
/*
            XIYOU LINUX
              ...............               
          ....  .  ...   .   .....          
        ...   . .:.:...:.-  -:.  ...        
      :.   :-::. :::----::. ..:::.  .:      
    .:   .-:.:-=++*+-:::-=+=-:. .-:   :.    
   :.  --:.--===++=        ===+=: ---  .:   
  :.    ..------=+-:+..=+: :===++=: .   .:  
 :.     :=====+++#+-+*#++- .*+====+:     .: 
.:     .==+*+*#%%@#-####%: .-++==--+.     : 
:.     -=+**+*##%#:*%*%@@@:  -++=---=     .:
:.-%+..-==+=##*=- *@@@@*+%#.  .==---=..+%-.:
: -++ .---+##+===-@@@@@*+#@#.   ---:=. ++- :
:.     -:=+===++*=+@@@@@@@@@+   .-::-     .:
.:     .::--++++==-*@@@@@@@@*    ::-:     : 
 :.     ::--=*##+=+-*@@@@@@%+  .+-.:     .: 
  :.     :+###%%#*.-@@@@@@%+#*+#%#=     .:  
   :.     *%%%%%%%**@@@%#+.+%%%%%%#=   .:   
    .:  -:=++**#%##+.:... .*###+=--:. :.    
      :...::....:-:::.:.:..::-::::: .:      
        ....:-..:.     :....:-.::...        
          ......::-::::-::.::....           
              ...:...........     
*/

#pragma once
#include<iostream>
#include <unistd.h>
using namespace std;
#include<sys/socket.h>
#include<string>
#include<sys/types.h>
#include<arpa/inet.h>
#include"myerror.hpp"
#include<stdlib.h>
#include<string.h>

class Ser_Con
{
public:
    static int Socket()
    {
        int sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0){
          myerror(string("socket"),__FILE__,__LINE__);
        }
        return sockfd;
    }

    static void Bind(const char *ip,int sockfd,int port)
    {
      struct sockaddr_in addr;
      memset(&addr,0,sizeof(addr));
      addr.sin_family=AF_INET;
      addr.sin_port=htons(port);
      inet_pton(AF_INET,ip,&addr.sin_addr);

      if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0){
        myerror(string("bind"),__FILE__,__LINE__);
      }
    }

    static void Listen(int sockfd,int nums)
    {
      if(listen(sockfd,nums)<0){
        myerror(string("listen"),__FILE__,__LINE__);
      }
    }
    
    static int Accept(int sockfd)
    {
      struct sockaddr_in clientaddr;
      memset(&clientaddr,0,sizeof(clientaddr));
      socklen_t addrlen=sizeof(clientaddr);
      int confd=accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen);
      if(confd<0){
        myerror(string("accept"),__FILE__,__LINE__);
      }
      return confd;
    }

    static void SetSockOpt(int sockfd)
    {
        //端口复用
        int opt=1;
        setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(opt));
    }

};


inline int readn(int fd, char *buf, int size)
{
  char *pt = buf;
  int count = size;
  while (count > 0)
  {
    int len = recv(fd, pt, count, 0);
    if (len == -1)
    {
      if (errno == EINTR || errno == EWOULDBLOCK)
        continue;
      else
        return -1;
    }
    else if (len == 0)
    {
      return size - count;
    }
    pt += len;
    count -= len;
  }
  return size - count;
}
inline int recvMsg(int fd, string &msg)
{
  int len = 0;
  readn(fd, (char *)&len, 4);
  len = ntohl(len);
  printf("接收到的 数据块大小 %d\n",len);
  char *data = (char *)malloc(len + 1);
  int Len = readn(fd, data, len);
  if (Len == 0)
  {
    printf("对方断开链接\n");
    close(fd);
  }
  else if (len != Len)
  {
    printf("数据接收失败\n");
  }
  data[len] = '\0';
  msg = data;
  return Len;
}