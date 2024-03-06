#include"../include/Allinclude.h"
#include <sys/epoll.h>
#include<Ser_Ok.hpp>


void Server::Ser_Register(struct epoll_event ep,Json::Value val)
{
    chatdb->my_database_connect("user");
    if(chatdb->my_database_user_exist(val["user"].asString())){
        Json::Value val; //新建json格式数据，往里面加入键值对
        val["cmd"]="register_reply"; //注册回复，结果失败
        val["result"]="failure";

        string s=Json::FastWriter.write(val);
        
        if(bu)
    }

}