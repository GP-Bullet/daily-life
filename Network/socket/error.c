#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
//?出错封装
//包含太多出错处理，代码会很乱

//我们通常只为了一个-1，而去搞一个int

void perr_exit(const char *s){
    perror(s);
    exit(1);
}
int Accept(int fd,struct sockaddr*sa,socklen_t *salenptr)
{
    int n;
again:   //啊这
    if((n=accept(fd,sa,salenptr))<0){//返回新的文件描述符
        if(errno==ECONNABORTED||(errno==EINTR))
        goto again;
    }else{
        perr_exit("accept error");
    }
    return n;
}
void Bind(int fd,struct sockaddr *sa,socklen_t salen)
{
    if(bind(fd,sa,salen)<0){
        perr_exit("bind error");
    }
}
void Connect(int fd,const struct sockaddr *sa,socklen_t salen)
{
    if(connect(fd,sa,salen)<0){
        perr_exit("connect error");
    }
}

void Listen(int fd,int backlog)
{
    if(listen(fd,backlog)<0){
        perr_exit("listen error");
    }
}

int Socket(int family,int type) 



ssize_t Read(int fd,void*ptr,size_t nbytes)
{
    ssize_t n;
again:
    if((n=read(fd,ptr,nbytes)))
}

ssize_t Write()

void Close()

readen
writeen
