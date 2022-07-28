#include <algorithm>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/FILE.h>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std;
int writen(int fd, char*msg,int size)
{
  char*buf=msg;
  int count =size;
  while(count>0)
  {
    int len=send(fd,buf,count,0);
    if(len==-1)
    {
      return -1;
    }
    else if(len==0)
    {
      continue;
    }
    buf+=len;
    count-=len;
  }
  return size;
}

int sendMsg(int fd,const char*msg,int len)
{
  if(fd<0||msg==NULL||len<=0)
  {
    return -1;
  }
  char*data=(char*)malloc(sizeof(char)*(len+4));
  int biglen=htonl(len);
  memcpy(data,&biglen,4);
  memcpy(data+4,msg,len);
  int ret;
  ret=writen(fd,data,len+4);
  if(ret==-1)
  {
    perror("send error");
    free(data);
    close(fd);
  }
  free(data);
  return ret;
}

#define SERVER_PORT 8000

void perr_exit(const char* s)
{
     perror(s);
     exit(-1);
}

int main() {
  
  // Server 端的监听地址

//不是一个wife
  struct sockaddr_in severaddr;
  int confd;
  int len,ret;
  char ipstr[] = "127.0.0.1";//..
  char *buf=NULL;
  // 1.创建一个socket
  confd = socket(AF_INET, SOCK_STREAM, 0);
  // 2.connect前知道自己服务器的ip和端口号
  //初始化服务器地址2
    
  bzero(&severaddr, sizeof(severaddr));
  severaddr.sin_family = AF_INET;
  inet_pton(AF_INET, ipstr, &severaddr.sin_addr.s_addr); // ip地址转换
  severaddr.sin_port = htons(SERVER_PORT);

  // 3.链接服务器
  //没有调bind，分配一个随机的端口号使用
  connect(confd, (struct sockaddr *)&severaddr,sizeof(severaddr)); // fd，地址记得强转，结构体长度

  // 4.请求服务器处理数据 
  for(;;){
      string str = "sdfsdafasdfasdf";
      len=str.size();
      if(len==0)continue;
      printf("发送出的 数据块len=%d\n",len);
      std::cout<<str<<std::endl;
      //strcpy(buf,str.c_str());


       ret=sendMsg(confd,buf,len);
       if(ret==-1){
         printf("sendMsg errno\n");
       }

  }
  // 5.关闭socket
  close(confd);
  return 0;
}
