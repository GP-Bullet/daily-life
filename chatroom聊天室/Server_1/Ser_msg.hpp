#pragma once
#include<iostream>
using namespace std;
#include<string>


class Message
{




private:
    int count;               //文件字符数计数
    int action;              //服务器接受动作,传输选择协议
    int flag;                //客户端接受动作
    int vip_flag;            //超级用户标志位
    int activity;            //发送表情短语状态切换
    int zan;                 //点赞标志位
    int pp_id;               //存放PPid号
    int to_id;               //存放对方PPid号 
    
    string name[20];           //存放当前昵称
    string passwd[20];         //存放密码
    string signer[25];         //存放个性签名
    string passpro[50];        //存放密保问题
    string passkey[50];        //存放密保答案
    string to_name[20];        //存放对方昵称
    string msg[300];           //存放聊天的内容
    string filename[20];       //存放文件名
    string filemsg[2048];      //存放string
};
/* 
   定义一个结构体,用来记录当前在线好友
   功能:主要为用户在线链表
                                       */
struct online
{
    int  online_flag;        //禁言标志位
    int  online_fd;          //连接描述符   
    int  online_id;          //在线用户ID
    
    string online_name[20];    //在线用户姓名

    struct online *next;
};
