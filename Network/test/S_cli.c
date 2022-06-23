#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
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
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
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

class ClientTester {
  friend void RunClientTest(std::shared_ptr<ClientTester> tester);
  using NT = NetworkTest::NT;
  using Stub = NetworkTest::NT::Stub;
  using Result = NetworkTest::Result;
  using runtime_error = std::runtime_error;
  using Context = ::grpc::ClientContext;

  std::unique_ptr<Stub> stub;
  std::default_random_engine re;
  std::uniform_int_distribution<char> AsciiStringGenerator;
  std::uniform_int_distribution<char> BinStringGenerator;
  std::uniform_int_distribution<uint32_t> LenGenerator;
  int fd;
  void QueryStatus(uint64_t idx, Result &response) {
    if (idx < 0)
      runtime_error("No Exist msg Idx<0\n");
    if (idx <= SuccessMaxIdx) {
      response.set_id(SuccessMaxIdx);
      response.set_reason(Success);
      return;
    }
    Context context;
    NetworkTest::Query query;
    query.set_id(idx);
    auto res = stub->ResultQuery(&context, query, &response);
    if (!res.ok())
      runtime_error("Test Error,Please Retry!\n");
    if (response.reason() >= ErrorLevel)
      throw std::runtime_error(
          ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
    if (response.reason() == Success)
      SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
  }
  void SendAnswer(const std::string &s) {
    SendSeq++;
    Context context;
    Result response;
    ::NetworkTest::Register answer;
    answer.set_content(s);
    auto res = stub->AnswerRegister(&context, answer, &response);
    if (!res.ok())
      runtime_error("Test Error,Please Retry!\n");
    if (response.reason() >= ErrorLevel)
      throw std::runtime_error(
          ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
    if (response.reason() == Success)
      SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
  }
  uint32_t SendSeq = -1;
  uint32_t SuccessMaxIdx = -1;
  static const char *ErrorCode2Msg(TestStatus s) noexcept {
    switch (s) {
    case Success:
      return "Success";
    case Wait:
      return "Wait For Msg";
    case WaitRPC:
      return "Wait For Test";
    case Diff:
      return "   is Error";
    case Unknow:
      return "Unknow Error";
    case ErrorLevel:
    case TestError:;
    }
    return "Tester is Error";
  }

  TestStatus Check() {
    using namespace std::chrono_literals;
    Result response;
    QueryStatus(SendSeq, response);
    if (response.id() == SendSeq && response.reason() == Success)
      return Success;
    std::this_thread::sleep_for(3s);
    return (response.id() == SendSeq && response.reason() == Success)
               ? Success
               : static_cast<TestStatus>(response.reason());
  }

  void genAsciiMsg(uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
      auto len = LenGenerator(re);
      auto ch = AsciiStringGenerator(re);
      std::string s(len, ch);
      SendAnswer(s);
      msgs->push(std::move(s));
    }
  }

  void genBinMsg(uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
      auto len = LenGenerator(re);
      std::string s;
      for (auto t = 0; t < len; t++)
        s.push_back(BinStringGenerator(re));
      SendAnswer(s);
      msgs->push(std::move(s));
    }
  }
  uint64_t getSeed() {
    fd = open("/dev/urandom", O_RDONLY);
    uint64_t seed;
    auto rc = read(fd, &seed, sizeof(seed));
    if (rc != sizeof(seed))
      throw runtime_error("read /dev/random failed");
    return seed;
  }

public:
  ClientTester(std::string addr)
      : stub(NT::NewStub(
            grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()))),
        re(getSeed()), msgs(std::make_shared<MsgBuf>()),
        AsciiStringGenerator(' ', '~'), BinStringGenerator(CHAR_MIN, CHAR_MAX),
        LenGenerator(0, 4096) {}
  std::shared_ptr<MsgBuf> msgs;
  void FinishCheck() {
    auto res = Check();
    if (res == Success) {
      puts("Congratulations! You Pass The Test!");
      _exit(0);
    }
    printf("Sorry! You did not pass all Test. Reason:%s  :(\n",
           ErrorCode2Msg(res));
  }
};
void RunClientTest(std::shared_ptr<ClientTester> tester) {
  try {
    using namespace std::chrono_literals;
    tester->genAsciiMsg(1);
    std::this_thread::sleep_for(2s);
    auto reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 1\n");
    }
    tester->genAsciiMsg(1);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 2\n");
    }
    tester->genAsciiMsg(1);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 3\n");
    }
    tester->genBinMsg(1);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 4\n");
    }
    tester->genBinMsg(1);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 5\n");
    }
    tester->genBinMsg(1);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 6\n");
    }
    tester->genAsciiMsg(1024);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 7\n");
    }
    tester->genBinMsg(1024);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 8\n");
    }
    tester->genAsciiMsg(1024);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 9\n");
    }
    tester->genBinMsg(1024);
    reslut = tester->Check();
    if (reslut != Success) {
      printf("QAQ: Failed at 10\n");
    }
    printf("Success Pass All Test\n");
    _exit(0);
  } catch (...) {
    printf("Exception:\n");
  }
}
std::shared_ptr<MsgBuf> InitTestClient(std::string addr) {
  try {
    auto tester = std::make_shared<ClientTester>(addr);
    auto test_thread = std::thread(RunClientTest, tester);
    test_thread.detach();
    return tester->msgs;
  } catch (std::exception &e) {

    printf("Exception: %s\n", e.what());
  }
  return nullptr;
}

struct Message {
  int msgID;
  int partID;
  std::string data;
};
class mess {
  int partid;
  int len;
};

//compile_commands.json 用来C++补全
//C++ share_ptr指针 
//std::move

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
  auto msg = InitTestClient("192.168.123.4:1234");
  // Put your code Here!
//192.168.30.144
//192.168.123.4
//不是一个wife
  struct sockaddr_in severaddr;
  int confd;
  int len,ret;
  char ipstr[] = "192.168.123.4";//..
  char buf[4096];

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
      auto str = msg->pop();
      len=str.size();
      if(len==0)continue;
      printf("len=%d\n",len);
      std::cout<<str<<std::endl;
      strcpy(buf,str.c_str());

       ret=sendMsg(confd,buf,len);
       if(ret==-1){
         printf("sendMsg errno\n");
       }

  }
  // 5.关闭socket
  //close(confd);
  return 0;
}
