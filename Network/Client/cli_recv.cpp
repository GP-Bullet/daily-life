#pragma once
#include"allinclude.h"

int readn(int fd, char *buf, int size)
{
  char *p = buf; //辅助指针记录位置
  int count = size;
  while (count > 0)
  {
    int len = recv(fd, p, count, 0);
    if (len == -1)
    {
      if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
      {
        continue;
      }
      perror("recve");
      return -1;
    }
    else if (len == 0)
    {                      //发送端端开连接
      return size - count; //返回总共读到的字节数
    }
    else
    {
      p += len;     //有效内存处继续接收数据
      count -= len; //还有多少没有接收
    }
  }
  return size;
}
//
//单纯地接受数据
int recvMsg(int cfd, char **msg)
{
  //第二个参数是一个传出参数
  // char head[4];
  int len = 0;
  readn(cfd, (char *)&len, 4); //先读取前面4个字节数
  int count = ntohl(len);      //网络字节序转换成主机字节序
  //printf("要接收的数据块的大小是:%d\n", count);                           把数据隐藏
  char *data = (char *)malloc(count + 1);
  int length = readn(cfd, data, count);
  if (length != count)
  {
    printf("接收数据失败\n");
    printf("%d->%d    %d\n", cfd, length, count);
    close(cfd);
    free(data);
    return -1;
  }

  data[count] = '\0';
  //printf("%s\n", data);                                          把数据隐藏
  *msg = data;
  return length;
}

//发送指定长度size的字符串
int writen(int cfd, const char *msg, int size)
{
  const char *buf = msg;
  int current = size;
  while (current > 0)
  {
    int len = send(cfd, buf, size, MSG_NOSIGNAL);
    //往对应的写缓冲区里面写内容，但是缓冲区内容有限
    //返回实际发送的字节数
    if (len == -1)
    {
      close(cfd);
      return -1;
    }
    else if (len == 0)
    {
      continue; //重新发送
    }
    else
    {
      buf += len;     //指针偏移
      current -= len; //剩余的字节数量
    }
  }
  return size;
}

//发送数据
int sendMsg(int cfd, std::string Msg, int len)
{
  if (cfd < 0 || Msg.size() < 0 || len <= 0)
  {
    return -1;
  }
  //将string类型的数据首先转化成指针类型
  const char *msg = Msg.c_str();
  char *data = (char *)malloc(len + 4);
  int biglen = htonl(len);
  memcpy(data, &biglen, 4);
  // printf("%d", data[0]);
  //内存拷贝，连续的4个字节数拷贝到内存中去
  //这四个字节数是包头
  // printf("cheng gong\n");
  memcpy(data + 4, msg, len);
  //将需要发送的内容进行拷贝
  int ret = writen(cfd, data, len + 4);
  if (ret == -1)
  {
    // perror("send\n");
    close(cfd);
  }
  return ret;
}