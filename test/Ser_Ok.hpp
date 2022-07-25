
#include <sys/epoll.h>
#define IP "127.0.0.1"
#define PORT 8000
#include"Ser_Epoll.hpp"


class Server
{
public:
    Server();
    ~Server();
    void InitServer()
    {
        ep=new Epoll();

    }
    void StartServer()
    {
        ep->Add();
        struct epoll_event
    }
private:
    Epoll *ep;
    
};