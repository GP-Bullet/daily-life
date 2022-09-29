#pragma once
#include "allinclude.h"
#include"ser_recv.cpp"
#include"ser_log.cpp"
#include"ser_fri.cpp"
#include"ser_gro.cpp"

#define PORT 10000
#define MAXLEN 4096
using namespace std;
string last_choice;
string last_path;
pthread_mutex_t mutexx;
int last_fd;
long long last_len = 0;


void Disband_group(jjjson::usr user)
{
    string s = "group";
    s += user.group;

    string value;
    json j;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Group>();
    for (auto it = tmp.member.begin(); it != tmp.member.end(); it++)
    {
        string t, v;
        json k;
        string r;
        t = "mygroup";
        t += *it;
        db->Get(leveldb::ReadOptions(), t, &v);     
        k = json::parse(v);
        auto tt = k.get<jjjson::myGroup>();
        for (auto i = tt.mygroup.begin(); i != tt.mygroup.end(); i++)
        {
            if (*i == user.group)
            {
                tt.mygroup.erase(i);
                // tt.status[user.group]=0;
                break;
            }
        }
        db->Delete(leveldb::WriteOptions(), t);
        k = tt;
        db->Put(leveldb::WriteOptions(), t, k.dump());

        pthread_mutex_lock(&mutexx);
        s = "mymessage" + *it;
        db->Get(leveldb::ReadOptions(), s, &v);
        k = json::parse(v);
        auto y = k.get<jjjson::mymessage>();
        char buf[4096];
        sprintf(buf, "the group :%s 已经被群主%s解散", user.group.c_str(), user.name.c_str());
        y.mes.push_back(buf);
        k = y;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, k.dump());
        pthread_mutex_unlock(&mutexx);
    }
    s="group"+user.group;
    db->Delete(leveldb::WriteOptions(), s); //删群
}

void Logout(jjjson::usr user)
{
    string value;
    string s = "friend";
    s += user.name;
    db->Get(leveldb::ReadOptions(), s, &value);
    json j = json::parse(value);
    auto tmp = j.get<jjjson::Friend>();
    // cout<<"lala"<<j<<endl;
    for (auto it = tmp.myfri.begin(); it != tmp.myfri.end(); it++)
    {
        string v;
        string t = "friend";
        t += *it;
        db->Get(leveldb::ReadOptions(), t, &v);
        json x = json::parse(v);
        auto q = x.get<jjjson::Friend>();
        for (auto i = q.myfri.begin(); i != q.myfri.end(); it++)
        {
            if (*i == user.name)
            {
                q.myfri.erase(i); //把我从好友的聊天列表删除
                db->Delete(leveldb::WriteOptions(), t);
                json c = q;
                db->Put(leveldb::WriteOptions(), t, c.dump());
                break;
            }
        }
        string w = user.name;
        w += *it;
        db->Delete(leveldb::WriteOptions(), w); //把我和它的聊天库删了
        w = *it;
        w += user.name;
        db->Delete(leveldb::WriteOptions(), w); //把它和我的聊天库删了
    }
    s = "mygroup";
    s += user.name;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto b = j.get<jjjson::myGroup>();
    for (auto it = b.mygroup.begin(); it != b.mygroup.end(); it++)
    {
        string vl;
        json q;
        string y = "group";
        y += *it;
        db->Get(leveldb::ReadOptions(), y, &vl);
        q = json::parse(vl);
        auto k = q.get<jjjson::Group>();
        if (k.owner == user.name) //注销的人是群主
        {
            user.group = *it;
            Disband_group(user);
            continue;
        }
        for (auto j = k.manager.begin(); j != k.manager.end(); j++)
        {
            if (*j == user.name)
            {
                k.manager.erase(j);
                break;
            }
        }
        for (auto m = k.member.begin(); m != k.member.end(); m++)
        {
            if (*m == user.name)
            {
                k.member.erase(m);
                break;
            }
        }
        q = k;
        db->Delete(leveldb::WriteOptions(), y); //改群信息表
        db->Put(leveldb::WriteOptions(), y, q.dump());

        s = "group_chat"; //删我和群的聊天表
        s += *it;
        s += user.name;
        db->Delete(leveldb::WriteOptions(), s);
    }
    s = "group";
    s += user.name;
    db->Delete(leveldb::WriteOptions(), s);
    char f[1];
    auto status = db->Delete(leveldb::WriteOptions(), user.name); //把自己删了
    string h = "friend";
    h += user.name;
    db->Delete(leveldb::WriteOptions(), h); //把自己的朋友表删除

    if (status.ok())
    {
        f[0] = '1';
    }
    else
    {
        f[0] = '0';
    }
    string x(f);
    sendMsg(user.fd, x, x.size());
}
void Withdraw_group(jjjson::usr user)
{
    string value;
    json j;
    string s = "group";
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Group>();
    if (user.name == tmp.owner) //群主要退群 (等于把群解散)
    {
        Disband_group(user);
    }

    else
    {
        for (auto it = tmp.manager.begin(); it != tmp.manager.end(); it++)
        {
            if (*it == user.name)
            {
                tmp.manager.erase(it);
                break;
            }
        }
        for (auto it = tmp.member.begin(); it != tmp.member.end(); it++)
        {
            if (*it == user.name)
            {
                tmp.member.erase(it);
                break;
            }
        }
        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        s = "mygroup";
        s += user.name;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto t = j.get<jjjson::myGroup>();
        for (auto i = t.mygroup.begin(); i != t.mygroup.end(); i++)
        {
            if (*i == user.group)
            {
                t.mygroup.erase(i);
                break;
            }
        }
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }
}
void Offline(jjjson::usr user)
{
    string value;
    char f[1];
    db->Get(leveldb::ReadOptions(), user.name, &value);
    json k = json::parse(value);
    auto tmp = k.get<jjjson::usr>();
    db->Delete(leveldb::WriteOptions(), user.name);
    tmp.status = 0;
    k = tmp;
    auto status = db->Put(leveldb::WriteOptions(), user.name, k.dump());
    
    pthread_mutex_lock(&mutexx);
    string s = "mymessage" + user.name;
    db->Get(leveldb::ReadOptions(), s, &value);
    k = json::parse(value);
    auto t = k.get<jjjson::mymessage>();
    t.mes.push_back("exit");
    k = t;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, k.dump());
    pthread_mutex_unlock(&mutexx);

    // cout << "thjis" << tmp.status << endl;

    if (status.ok())
    {
        f[0] = '1';
    }
    else
        f[0] = '0';
    string x(f);
    sendMsg(user.fd, x, x.size());
}




void *task(jjjson::usr arg)
{
    //pthread_detach(pthread_self());
    // cout << last_choice << endl;
    char buf[4096];
    memset(buf, 0, 4096);
    // int len =0;

    // while((len=recv(tmpfd, buf, 4096, 0))<=0);
    // cout<<len<<endl;
    // cout<<errno<<endl;
    // cout<<buf<<endl;
    if (errno == 11)
    {
        cout << "on" << endl;
        errno = 0;
        return NULL;
    }

    // buf[len] = '\0';
    //  cout << "tes;t" << buf << endl;
    // if (len == 0)
    //{   cout<<"oyeah!"<<endl;
    //   epoll_ctl(epollfd, EPOLL_CTL_DEL, tmpfd, NULL);
    //  close(tmpfd);
    //}
    // else
    {
        // string s(buf);
        // cout << s << endl;
        // json t = json::parse(s);
        // cout<<"1"<<endl;
        jjjson::usr user = arg;
        cout<<"user_fri"<<user.mes_fri<<endl;
        user.fd = tmpfd;
        jjjson::usr tmp = user;
        // cout << user.mes_fri << endl;
        if (tmp.choice.compare("sign") == 0)
        {
            Sign(user);
        }
        else if (tmp.choice.compare("login") == 0)
        {
            Login(user);
        }
        else if (tmp.choice.compare("add_friend") == 0)
        {
            add_friend(user);
        }
        else if (tmp.choice.compare("settings") == 0)
        {
            Settings(user);
        }
        else if (tmp.choice.compare("offline") == 0)
        {
            Offline(user);
        }
        else if (tmp.choice.compare("check_friend") == 0)
        {
            Check_friend(user);
        }
        else if (tmp.choice.compare("friend_req") == 0)
        {
            string value;
            string s = "friend";
            s += user.name;
            auto status = db->Get(leveldb::ReadOptions(), s, &value);
            // cout << "look:" << value.c_str() << endl;
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("agree_friend") == 0 || tmp.choice.compare("reject_friend") == 0)
        {
            Deal_friendreq(user);
        }
        else if (tmp.choice.compare("look_friend") == 0)
        {
            string value;
            string s = "friend";
            s += user.name;
            auto status = db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
           
            json j = json::parse(value);
            auto tmp = j.get<jjjson::Friend>();
            for (auto it = tmp.myfri.begin(); it != tmp.myfri.end(); it++)
            {
                char f[1];
                string val;
                db->Get(leveldb::ReadOptions(), *it, &val);
                j = json::parse(val);
                auto t = j.get<jjjson::usr>();
                if (t.status == 0)
                {
                    f[0] = '0';
                }
                else
                {
                    f[0] = '1';
                }
                string x(f);
                sendMsg(user.fd, x, x.size());
            }
        }
        else if (tmp.choice.compare("check") == 0)
        {
            string value;
            auto status = db->Get(leveldb::ReadOptions(), user.name, &value);
            json j = json::parse(value);
            auto us = j.get<jjjson::usr>();
            char f[1];
            if (us.box.empty())
            {
                f[0] = '0';
            }
            else
            {
                f[0] = '1';
            }
            string x(f);
            sendMsg(user.fd, x, x.size());
        }
        // else if (tmp.choice.compare("inform") == 0)
        //{  pthread_t ttid;
        // pthread_create(&ttid,NULL,Inform,(void *)&user);
        // Inform(user);
        //}

        else if (tmp.choice.compare("delete_friend") == 0)
        {
            Delete_fri(user);
        }
        else if (tmp.choice.compare("chat_sb") == 0)
        {
            Chat_sb(user);
        }
        else if (tmp.choice.compare("quit_chatfri") == 0)
        {
            string value;
            db->Get(leveldb::ReadOptions(), user.name, &value);
            json j = json::parse(value);
            auto t = j.get<jjjson::usr>();
            t.choice = " ";
            t.friendname = " ";
            t.mes_fri = "quit";
            j = t;
            string z = j.dump();
            db->Delete(leveldb::WriteOptions(), user.name);
            db->Put(leveldb::WriteOptions(), user.name, z);

            string zz = "quit";
            sendMsg(user.fd, zz, zz.size());
        }

        // else if (tmp.choice.compare("recv_mes") == 0)
        // {
        //     string value;
        //     db->Get(leveldb::ReadOptions(), user.name, &value);
        //     json j = json::parse(value);
        //     auto t = j.get<jjjson::usr>();
        //     t.choice = "chat_sb";
        //     t.friendname = user.friendname;
        //     t.mes_fri = "";
        //     j = t;
        //     string z = j.dump();
        //     db->Delete(leveldb::WriteOptions(), user.name);
        //     db->Put(leveldb::WriteOptions(), user.name, z);
        //     pthread_create(&tid, NULL, Recv_mes, (void *)(&tmp));
        //     // Recv_mes((void*)&user);
        // }
        else if (tmp.choice.compare("check_history") == 0)
        { // printf("enter");
            Check_history(user);
        }
        else if (tmp.choice.compare("start_shield") == 0 || tmp.choice.compare("canel_shield") == 0)
        {
            Shield_fri(user);
        }
        else if (tmp.choice.compare("check_shield") == 0)
        { // cout<<"hepp"<<endl;
            string s = "friend";
            s += user.name;
            string value;
            db->Get(leveldb::ReadOptions(), s, &value);
            // cout<<"jjj"<<value<<endl;
            json j = json::parse(value);
            auto tmp = j.get<jjjson::Friend>();
            char f[1];
            if (tmp.ship[user.friendname] == 0)
            {
                f[0] = '1';
            }
            else
            {
                f[0] = '0';
            }
            string x(f);
            sendMsg(user.fd, x, x.size());
        }
        else if (tmp.choice.compare("logout") == 0)
        {
            Logout(user);
        }
        else if (tmp.choice.compare("find_pwd") == 0)
        {
            Find_pwd(user);
        }
        else if (tmp.choice.compare("true_pwd") == 0)
        {
            True_pwd(user);
        }
        else if (tmp.choice.compare("build_group") == 0)
        {
            Build_create(user);
        }
        else if (tmp.choice.compare("join_group") == 0)
        {
            Join_group(user);
        }
        else if (tmp.choice.compare("group_req") == 0)
        {
            string value;
            string s = "group";
            s += user.group;
            db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("agree_group") == 0 || tmp.choice.compare("reject_group") == 0)
        {
            Deal_group_req(user);
        }
        else if (tmp.choice.compare("look_group") == 0)
        {
            string value;
            value.clear();
            string s = "mygroup";
            s += user.name;
            db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("check_member") == 0)
        {
            string value;
            value.clear();
            string s = "group";
            s += user.group;
            db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("set_manager") == 0 || tmp.choice.compare("canel_manager") == 0)
        {
            Set_manager(user);
        }
        else if (tmp.choice.compare("kick_sb") == 0)
        {
            Kick_sb(user);
        }
        else if (tmp.choice.compare("look_g") == 0)
        {
            Look_g(user);
        }
        else if (tmp.choice.compare("disband_group") == 0)
        {
            Disband_group(user);
        }
        else if (tmp.choice.compare("withdraw_group") == 0)
        {
            Withdraw_group(user);
        }
        else if (tmp.choice.compare("chat_group") == 0)
        {
            Chat_group(user);
        }
        else if (tmp.choice.compare("offline_mes_gro") == 0)
        {
            Offline_mes_gro(user);
        }
        else if (tmp.choice.compare("offline_mes_fri") == 0)
        {
            Offline_mes_fri(user);
        }
        else if (tmp.choice.compare("check_group_history") == 0)
        {
            Check_group_history(user);
        }
        else if (tmp.choice.compare("recv_file_fri") == 0)
        {
            json j;
            string value;
            string s;
            char buf[1024];
            memset(buf, 0, 1024);
            s = "mymessage" + user.friendname;
            db->Get(leveldb::ReadOptions(), s, &value);
            j = json::parse(value);
            auto tmp = j.get<jjjson::mymessage>();
            sprintf(buf, "%s send a file: %s to you", user.name.c_str(), user.filename.c_str());
            string t(buf);
            tmp.mes.push_back(t);
            j = tmp;
            db->Delete(leveldb::WriteOptions(), s);
            db->Put(leveldb::WriteOptions(), s, j.dump());

            Recv_file_fri(user);
        }
        else if (tmp.choice.compare("send_file_fri") == 0)
        {
            Send_file_fri(user);
        }
        else if (tmp.choice.compare("check_file") == 0)
        {
            string s;
            string value;
            json j;
            s = user.name;
            s += user.friendname;
            db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("recv_file_gro") == 0)
        {
            Recv_file_gro(user);
        }
        else if (tmp.choice.compare("check_file_gro") == 0)
        {
            string s = "group_chat";
            string value;
            json j;
            s += user.group;
            s += user.name;
            db->Get(leveldb::ReadOptions(), s, &value);
            sendMsg(user.fd, value, value.size());
        }
        else if (tmp.choice.compare("send_file_gro") == 0)
        {
            Send_file_gro(user);
        }
        else if (tmp.choice.compare("file_size") == 0)
        {
            json j;
            string s;
            string path = "/home/chenzhenxxx/chatroom/" + user.filename;
            struct stat st;
            lstat(path.c_str(), &st);
            jjjson ::usr k;
            k.id = st.st_size;
            j = k;
            s = j.dump();
            sendMsg(user.fd, s, s.size());
        }
    }
    return NULL;
}