#include <sys/epoll.h>
#define IP "127.0.0.1"
#define PORT 8000
#define ListenNum 1024
#include"Ser_Epoll.hpp"
#include"Ser_Sock.hpp"
#define OPEN_MAX 4096
#include"../include/Allinclude.h"

class Server
{

private:
    Epoll *ep;
    int m_listenfd;
    int m_efd;
    static ChatDataBase *chatdb;
public:
    Server()
    {
        ep=new Epoll();
        m_listenfd=Ser_Con::Socket();
        Ser_Con::SetSockOpt(m_listenfd);
        Ser_Con::Bind(IP,m_listenfd,PORT);
        Ser_Con::Listen(m_listenfd,ListenNum);
        m_efd=ep->Create();
    }
    
    ~Server()
    {
        close(m_listenfd);
        close(m_efd);
        delete ep;
    }

    void ServerCtl()
    {
        string buf;
        struct epoll_event eparr[OPEN_MAX];
        ep->Add(m_listenfd);
        while(1){
            cout<<"1"<<endl;
            int nready=ep->Wait(eparr);
            for(int i=0;i<nready;i++){
                if(eparr[i].data.fd==m_listenfd){
                    int confd=Ser_Con::Accept(m_listenfd);
                    ep->Add(confd);
                }else{
                    int ret;
                    ret=recvMsg(eparr[i].data.fd, buf);

                    std::cout<<buf<<std::endl;
                }
            }
        }
    }

    void Ser_Register(struct epoll_event ep,Json::Value val);
};