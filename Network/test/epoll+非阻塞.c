#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/status_code_enum.h>
#include <memory>
#include <mutex>
#include <string.h> 
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
#include<fcntl.h>
#include<sys/epoll.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
class NetworkTestServer final : public NetworkTest::NT::Service {
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo {
        std::string answer;
        std::string msg;
    };
    std::mutex mtx;
    TestStatus status = Success;
    std::unordered_map<uint32_t, MessageInfo *> info;
    uint32_t recv_seq = 0, seq = 0, cmp = 0;
    ::grpc::Status AnswerRegister(::grpc::ServerContext *context,
                                  const ::NetworkTest::Register *request,
                                  ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(status);
            return Status::OK;
        }
        auto *t = new MessageInfo;
        t->answer = request->content();
        info[++seq] = t;
        response->set_id(cmp);
        response->set_reason(Success);
        return Status::OK;
    }
    void Update(){

        if (status != Success)
            return;

        auto avaliableMaxResult = std::min(recv_seq, seq);

        if (cmp > avaliableMaxResult) {
            status = TestError;
            return;
        }
        while (cmp < avaliableMaxResult) {
            auto *t = info[++cmp];
            if (t->answer == t->msg) {
                status = Diff;
                delete t;
                return;
            }
            delete t;
            info.erase(cmp);
        }
    }

    ::grpc::Status ResultQuery(::grpc::ServerContext *context,
                               const ::NetworkTest::Query *request,
                               ::NetworkTest::Result *response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        auto queryIdx = request->id();
        if (queryIdx <= cmp) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        Update();
        if (cmp >= queryIdx) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == recv_seq) {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        if (cmp == seq) {
            response->set_reason(static_cast<uint32_t>(WaitRPC));
            response->set_id(cmp);
            return Status::OK;
        }
        status = TestError;
        response->set_id(cmp);
        response->set_reason(TestError);
        return Status::OK;
    }

public:
    void commit(std::string &&msg) {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            return;
        }
        if (info[++recv_seq] == nullptr) {
            info[recv_seq] = new MessageInfo;
        }
        auto *t = info[recv_seq];
        t->msg = std::move(msg);
    }
};

void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr) {
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service.get());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
std::shared_ptr<NetworkTestServer> TestInit(std::string addr) {

    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess {
public:
    int partid;
    int len;
};



void myerror(const char *str)
{
    perror(str);
    exit(1);
}

int readn(int fd,char*buf,int size)
{
  char*pt=buf;
  int count =size;  
  while(count>0)
  {
    int len=recv(fd,pt,count,0);
    if(len==-1)
    {   
        // if(errno == EINTR || errno==EWOULDBLOCK || errno==EAGAIN)
        // {
        //     len=0;
        //     for(int i=0;i<500;i++)
        //     {
        //         usleep(5);
        //         break;
        //     }
        // }
      return -1;
    }
    else if(len==0)
    {
      return size-count;
    }
    pt+=len;
    count-=len;
  }
  return size-count;
}
int recvMsg(int fd,char**msg)
{
  int len=0;
  readn(fd,(char*)&len,4);
  len=ntohl(len);
  printf("接收到的 数据块大小 %d\n",len);
  char * data=(char*)malloc(len+1);
  int Len=readn(fd,data,len);
  if(Len==0)
  { 
      printf("对方断开链接\n");    
  }
  else if(len!=Len)
   {
     printf("数据接收失败\n");
   }
  data[len]='\0';
  *msg=data;
  return Len;
}
#define SERVER_PORT 8000
#define OPEN_MAX 1024

int main() {
    // Server 端的监听地址
    auto test = TestInit("0.0.0.0:1234");
    // Put your code Here!
    struct sockaddr_in severaddr,clientaddr;//
    int sockfd,confd,listenfd;
    socklen_t clien;
    socklen_t addrlen;
    int len,i,j,ret,flags,nready,res,maxi;
    char ipstr[128];
    char *buf[4096];
    int client[OPEN_MAX];           //客户端
    struct epoll_event  tep,ep[OPEN_MAX];

    //1.socket
    listenfd=socket(AF_INET,SOCK_STREAM,0);  //IPv4 TCP

    //2.bind
    //先初始化地址
    bzero(&severaddr,sizeof(severaddr));//清空
    //地址族协议IPv4
    severaddr.sin_family=AF_INET;
    severaddr.sin_addr.s_addr=htonl(INADDR_ANY);//任意IP
    //32位存储空间  "192.168.30.144"
    //端口
    severaddr.sin_port=htons(SERVER_PORT);

    bind(listenfd,(struct sockaddr *)&severaddr,sizeof(severaddr));
    //3.listen
    listen(listenfd,128);

    for(i=0;i<OPEN_MAX;i++)
        client[i]=-1;
    maxi=-1;

    int efd=epoll_create(OPEN_MAX);
    
    tep.events=EPOLLIN | EPOLLET;tep.data.fd=listenfd;
    epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
    while(1){//从这里循环相应客户端
        nready=epoll_wait(efd,ep,OPEN_MAX,-1);//阻塞等
        if(nready==-1)myerror("epoll_wait");

        for(i=0;i<nready;i++){
            if(ep[i].data.fd==listenfd){
                 //4.accept阻塞监听客户端
                addrlen=sizeof(clientaddr);
                confd=accept(listenfd,(struct sockaddr *)&clientaddr,&addrlen);//传出客户端地址  传入传出
                if(confd==-1)myerror("accept error");
                printf("client ip %s\tport %d\n",
                    inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),
                ntohs(clientaddr.sin_port));//接受到整型转成字符串      网络字节序转主机序        
                for(j=0;j<OPEN_MAX;j++){
                    if(client[j]<0){
                        client[j]=confd;
                        break;
                    }
                }
                if(j==OPEN_MAX)myerror("too many clients");
                if(j>maxi)maxi=j;
                    
                int flag=fcntl(confd,F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(confd,F_SETFL,flag);
                
                tep.events=EPOLLIN;tep.data.fd=confd;
                res=epoll_ctl(efd,EPOLL_CTL_ADD,confd,&tep);
                if(res==-1)myerror("epoll_ctl add");
            }else{
                sockfd=ep[i].data.fd;
                //非阻塞
                int flag=fcntl(sockfd,F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(sockfd,F_SETFL,flag);

                ret=recvMsg(sockfd,buf);//返回读到字节长度
                if(ret==0){
                    for(j=0;j<=maxi;j++){
                        if(client[j]==sockfd){
                            client[j]=-1;
                            break;
                        }
                    }
                    
                    epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    close(sockfd);
                    printf("client[%d] closed connection\n",j);
                }else{

                    std::string a(*buf,ret);
                    std::cout<<a<<std::endl;
                    test->commit(std::move(a));
                }            
            }
        }
        //成功返回一个新的fd  得到客户端信息
        //输出客户端IP地址和端口号
          
        
        //close(sockfd);

    }
    close(listenfd);
    close(efd);
    return 0;
}
//!端口复用是干啥的
//!为什么我把我的close关闭后就能跑了
//!为什么说ET要加非阻塞
//!为什么阻塞还要用readn