#ifndef JSON_USE_H__
#define JSON_USE_H__
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
extern pthread_mutex_t mutexx;
extern string last_choice;
extern string last_path;
extern int last_fd;
extern long long last_len;


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