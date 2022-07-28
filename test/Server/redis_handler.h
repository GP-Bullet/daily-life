#ifndef __REDIS_HANDLER_H__
#define __REDIS_HANDLER_H__
 
#include <hiredis/hiredis.h>
#include <string>

using namespace std;

enum
{
    M_REDIS_OK = 0, //执行成功
    M_CONNECT_FAIL = -1, //连接redis失败
    M_CONTEXT_ERROR = -2, //RedisContext返回错误
    M_REPLY_ERROR = -3, //redisReply错误
    M_EXE_COMMAND_ERROR = -4 //redis命令执行错误
};


class RedisHandler
{
public:
    RedisHandler();
    ~RedisHandler();
    int connect(const string &addr, int port, const string &pwd = ""); //连接redis数据库：addr：IP地址，port：端口号，pwd：密码(默认为空)
    int disConnect(); //断开连接

    int setValue(const string &key, const string &value); //添加或修改键值对，成功返回0，失败<0
    int getValue(const string &key, string &value); //获取键对应的值，成功返回0，失败<0
    int delKey(const string &key); //删除键，成功返回影响的行数，失败<0
    int printAll(); //打印所有的键值对

    string getErrorMsg(); //获取错误信息
private:
    string m_addr; //IP地址
    int m_port; //端口号
    string m_pwd; //密码
    redisContext* pm_rct; //redis结构体
    redisReply* pm_rr; //返回结构体
    string error_msg; //错误信息

    int connectAuth(const string &pwd); //使用密码登录
    int handleReply(void* value = NULL, redisReply ***array = NULL); //处理返回的结果
};


#endif
