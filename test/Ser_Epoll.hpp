#pragma once

#include<sys/epoll.h>
#include<string>
#include<unistd.h>
#include <hiredis/hiredis.h> 
#include<myerror.h>
#include<string.h>
#include<fcntl.h>

#define OPEN_MAX 4096 
class Epoll
{
public:
    static int Create()
    {
        int epfd=epoll_create(4096);
        if(epfd<0){
            myerror(string("epoll_create"),__FILE__,__LINE__);
        }
        return epfd;
    }
    void Add(int sockfd)
    {
        struct epoll_event tep;
        tep.data.fd=sockfd;
        tep.events=EPOLLIN|EPOLLET;
        
        int flag=fcntl(sockfd,F_GETFL,0);
        fcntl(sockfd,F_SETFL,flag | O_NONBLOCK);
        epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&tep);
    }
    int Wait(struct epoll_event *event)
    {
        int ret=epoll_wait(epollfd,event,OPEN_MAX,-1);
        if(ret<0){
            myerror(string"epoll_wait",__FLIE__,__LINE__);
        }
        return ret;
    }
    void DEL(int sockfd)
    {
        struct epoll_event tep;
        tep.data.fd=sockfd;
        tep.events=EPOLLIN;
        epoll_ctl(epollfd,EPOLL_CTL_DEL,sockfd,&tep);
    }

private:
    int epollfd;

}

