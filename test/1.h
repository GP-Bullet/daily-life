#ifndef SERVER_H
#define SERVER_H

#include<sys/epoll.h>
#include<string>
#include<unistd.h>


void myerror(const char*str)
{
    perror(str);
    exit(1);
}
#define PORT 8000
class Server
{
public:
    Server(const char *ip="127.0.0.1",int port=PORT);
    ~Server();
private:
    struct epoll_event ep;  //事件集合
                            //监听事件
};


#endif