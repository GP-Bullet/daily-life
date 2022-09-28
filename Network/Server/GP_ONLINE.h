/*********************************************************
-  Copyright (C): 2016
-  File name    :PP_ONLINE.h
-  Author       :- Zhao -
-  Date         :2016年01月29日 星期五 20时56分45秒
-  Description  :
*  *******************************************************/
/* 条件编译 */
#ifndef PP_ONLINE_H_
#define PP_ONLINE_H_

/* 头文件 */
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sqlite3.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
 
/* 宏定义 */
#define LOGIN           0    //宏定义登录action
#define REGIST          1    //宏定义注册action
#define FIND_PASSPRO    2    //宏定义找到密保问题action    
#define DIS_ONLINE_USER 3    //宏定义查看在线好友action
#define CHATONE         4    //宏定义私聊action
#define CHATALL         5    //宏定义群聊action
#define RESET_PASSWD    6    //宏定义修改密码action
#define HELP            7    //宏定义帮助action
#define BACK_LOGMENU    8    //宏定义返回登录界面action
#define SLENCE          9    //宏定义禁言action
#define PERMITE        10    //宏定义解禁action
#define TICK           11    //宏定义踢人action
#define EXIT           12    //宏定义退出action
#define SUCCESS        13    //宏定义成功
#define LOGINSUPER     15    //宏定义超级用户
#define SLENCEALREADY  16    //宏定义已经禁言
#define PERMITEALREADY 17    //宏定义已经解禁
#define DIS_SUCCESS    18    //宏定义查看好友结束
#define TICKFAIL       19    //宏定义踢人失败
#define PERMITESUCCESS 20    //宏定义解禁成功给VIP
#define SLENCESUCCESS  21    //宏定义禁言成功给VIP
#define TICKOK         22    //宏定义踢人返回给VIP
#define TICKSUCCESS    23    //宏定义踢人成功
#define PERMITEFAIL    24    //宏定义解禁的对象不存在
#define SLENCEFAIL     25    //宏定义禁言用户不存在
#define CHATONEFAIL    26    //宏定义私聊用户不存在
#define LOGINFAIL      27    //宏定义登录用户已在线
#define PASSKEY_ERROR  28    //宏定义密保答案回答错误
#define RESET_SUCCESS  29    //宏定义密码改动成功
#define SETSIGNER      30    //宏定义设置个性签名
#define VIPMEMBER      31    //宏定义注册会员
#define SENDBQ         32    //宏定义发送表情
#define SENDDY         33    //宏定义发送短语
#define SENDFILE       34    //宏定义发送文件
#define DISJILU        35    //宏定义查看聊天记录
#define VIPEXIT        36    //宏定义VIP注册退出
#define SENDFILE_ERROR 37    //宏定义发送文件失败，对方用户不在线
#define SENDFILETOSELF 38    //宏定义发送文件给自己
#define CHATONETOSELF  39    //宏定义私聊和自己
#define DIANZAN        40    //宏定义点赞
#define DIANZANFAIL    41    //宏定义点赞失败
#define WRONG_CMD      14    //宏定义输入指令出错action
#define USERIDERROR    -2    //宏定义ID出错
#define USERPASSERR    -3    //宏定义密码出错
#define BUFFSIZE       1024  //数据缓冲区大小
#define portnumber     8000  //端口号8000

/* 
   定义一个结构体,用来封装消息,供服务器客户端通信 
                                                  */
typedef struct _Message
{
    int count;               //文件字符数计数
    int action;              //服务器接受动作,传输选择协议
    int flag;                //客户端接受动作
    int vip_flag;            //超级用户标志位
    int activity;            //发送表情短语状态切换
    int zan;                 //点赞标志位
    int pp_id;               //存放PPid号
    int to_id;               //存放对方PPid号 
    
    char name[20];           //存放当前昵称
    char passwd[20];         //存放密码
    char signer[25];         //存放个性签名
    char passpro[50];        //存放密保问题
    char passkey[50];        //存放密保答案
    char to_name[20];        //存放对方昵称
    char msg[300];           //存放聊天的内容
    char filename[20];       //存放文件名
    char filemsg[2048];      //存放文件内容

}Message;

/* 
   定义一个结构体,用来记录当前在线好友
   功能:主要为用户在线链表
                                       */
struct online
{
    int  online_flag;        //禁言标志位
    int  online_fd;          //连接描述符   
    int  online_id;          //在线用户ID
    
    char online_name[20];    //在线用户姓名

    struct online *next;
};

/* 
   定义全局变量 
                */
extern struct online *head;
extern struct online *new_user;
extern pthread_mutex_t mutex;    //互斥锁
extern sqlite3* db;

/* 
   函数声明
           */

void log_dis(void);       //登录界面动态
void log_dis2(void);      //登录界面静态
void reg_dis(void);       //注册界面
void help_dis(void);      //帮助界面 
void user_dis(void);      //用户界面
void clear_min(void);     //请屏小窗口
void loading_dis(void);   //聊天室开机加载动画
void rem_passwd(void);    //修改密码界面
void superuser_dis(void); //超级用户界面
int  input_check(char *); //字符串解析动作
void file_recv(struct _Message *);      //文件读取线程
int  pack_msg(int, Message *, int, int);//客户端数据打包
void client_read_msg(void *);           //客户端读线程
void server_read_msg(void *);           //服务器读线程
int  rand_brith_id(void);               //6位的随机数产生函数,用来获取qq号
void create_server_sql(sqlite3 *);      //创建数据库
int  find_id_inbase(sqlite3 *, int);    //查询IDs是否重复
void insert_user_to_ppbase(sqlite3 *, struct _Message *); //将好友信息添加到数据库
int  check_passwd_inbase(sqlite3 *, int, char *);         //登录信息核对
void find_logname_inbase(sqlite3 *, struct _Message *);   //根据上线ID得到该用户昵称
void find_passpro_inbase(sqlite3 *, struct _Message *);   //根据ID得到该用户的密保问题
void find_passkey_inbase(sqlite3 *, struct _Message *);   //根据ID得到该用户的密保答案并判断与用户输入是否一致
void set_vipflag_inbase(sqlite3 *, struct _Message *);    //根据ID更新数据库中的VIP_flag
void update_signer_inbase(sqlite3 *, struct _Message *);  //根据ID更新数据库中的个性签名 
void update_zan_inbase(sqlite3 *, struct _Message *);     //根据ID更新数据库中的赞


#include <iostream>
#include<iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <stdlib.h>
#include<pthread.h>
#include <string>
#include<netinet/tcp.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/socket.h>
#include<sys/epoll.h>
#include <sys/stat.h>
#include<pthread.h>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp> //引入json.hpp，该文件已经放在系统默认路径：/usr/local/include/nlohmann/json.hpp
#include<leveldb/db.h>
#include<sys/sendfile.h>
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"
#define SHINE "\033[5m"      //闪烁
#define DASH "\033[9m"       // 中间一道横线
#define QUICKSHINE "\033[6m" //快闪
#define FANXIAN "\033[7m"    //反显
#define XIAOYIN "\033[8m"    // 消隐，消失隐藏

leveldb::DB *db;
using namespace std;
// for convenience
using json = nlohmann::json;
#define PORT 10000
#define MAXLEN 4096
int tmpfd;
int epollfd;
pthread_t tid;
namespace jjjson
{
    class usr
    {
    public:
        long long id;
        int fd;
        string friendname;
        int friendid;
        string name;
        string pwd;
        int status;
        string question;
        string answer;
        string choice;
        string mes_fri;
        time_t time;
        string group;
        vector<string> box;
        string buf;
        string filename;
    };
    
    class Friend
    {   public:
        vector<string> myfri;
        vector<string> request;
        string from;
        string to;
        vector<string> buf;
        vector<int> time;
        map<string,int> ship;

    };

    class Fri_chat
    {
        public:
         vector<string> history;
         vector<string>unread;
         vector<time_t> time;
         vector<time_t> unread_t;
         vector<string> file;

    };
    class Group
    {   public:
        string owner;
        vector<string> manager;
        vector<string> member;
        vector<string> join_req;
        vector<string> history;
        vector<time_t> time;
    };
    class myGroup
    {
        public:
        vector<string> mygroup;
        map<string,int>status;
       
    };
    class Gro_chat
    {
        public:
        vector<string> unread_mes;
        vector<time_t> unread_t;
        vector<string> filename;
    };
     class mymessage
    {   public:
        vector<string> mes;
    };



    void to_json(json &j, const usr &p)
    {
        j = json{{"friendname",p.friendname},{"friendid",p.friendid},{"id",p.id}, {"fd", p.fd},{"name", p.name},{"pwd",p.pwd},{"status",p.status},{"question",p.question},{"answer",p.answer},{"choice",p.choice},{"box",p.box},{"time",p.time},{"mes_fri",p.mes_fri},{"group",p.group},{"buf",p.buf},{"filename",p.filename}};
    }
    void from_json(const json &j, usr &p)
    {
        j.at("name").get_to(p.name);
        j.at("id").get_to(p.id);
        j.at("pwd").get_to(p.pwd);
        j.at("fd").get_to(p.fd);
        j.at("status").get_to(p.status);
        j.at("question").get_to(p.question);
        j.at("answer").get_to(p.answer);
        j.at("choice").get_to(p.choice);
        j.at("box").get_to(p.box);
        j.at("friendname").get_to(p.friendname);
        j.at("friendid").get_to(p.friendid);
        j.at("mes_fri").get_to(p.mes_fri);
        j.at("time").get_to(p.time);
        j.at("group").get_to(p.group);
        j.at("buf").get_to(p.buf);
        j.at("filename").get_to(p.filename);
    }
    void to_json(json &j,const Friend &p)
    {
        j=json{{"myfri",p.myfri},{"request",p.request},{"from",p.from},{"to",p.to},{"buf",p.buf},{"time",p.time},{"ship",p.ship}};
    }
    void from_json(const json &j,Friend &p)
    {
        j.at("myfri").get_to(p.myfri);
        j.at("request").get_to(p.request);
        j.at("from").get_to(p.from);
        j.at("to").get_to(p.to);
        j.at("buf").get_to(p.buf);
        j.at("time").get_to(p.time);
        j.at("ship").get_to(p.ship);

    }

    void to_json(json &j,const Fri_chat &p)
    {
        j=json{{"history",p.history},{"unread",p.unread},{"time",p.time},{"unread_t",p.unread_t},{"file",p.file}};
    }
    void from_json(const json &j,Fri_chat &p)
    {
        j.at("history").get_to(p.history);
        j.at("unread").get_to(p.unread);
        j.at("time").get_to(p.time);
        j.at("unread_t").get_to(p.unread_t);
        j.at("file").get_to(p.file);
    }
    void to_json(json &j,const Group &p)
    {
        j=json{{"owner",p.owner},{"manager",p.manager},{"member",p.member},{"join_req",p.join_req},{"history",p.history},{"time",p.time}};
    }
    void from_json(const json &j,Group &p)
    {
        j.at("owner").get_to(p.owner);
        j.at("manager").get_to(p.manager);
        j.at("member").get_to(p.member);
        j.at("join_req").get_to(p.join_req);
        j.at("history").get_to(p.history);
        j.at("time").get_to(p.time);
        

    }
    void to_json(json &j,const myGroup &p)
    {
        j=json{{"mygroup",p.mygroup},{"status",p.status}};
    }
    void from_json(const json &j,myGroup &p)
    {
        j.at("mygroup").get_to(p.mygroup);
        j.at("status").get_to(p.status);
        

    }
    void to_json(json &j,const Gro_chat &p)
    {
        j=json{{"unread_mes",p.unread_mes},{"unread_t",p.unread_t},{"filename",p.filename}};
    }
    void from_json(const json &j,Gro_chat &p)
    {
        j.at("unread_mes").get_to(p.unread_mes);
        j.at("unread_t").get_to(p.unread_t);
        j.at("filename").get_to(p.filename);
    }
    void to_json(json &j,const mymessage &p)
    {
        j=json{{"mes",p.mes}};
    }
    void from_json(const json &j,mymessage &p)
    {
       
        j.at("mes").get_to(p.mes);
        

    }

   
}

#endif
