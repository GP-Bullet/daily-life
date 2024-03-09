#pragma once
#include"allinclude.h"
#include"ser_recv.cpp"
#include"ser_thread.cpp"


void Sign(jjjson::usr user)
{
    string value;
    json j = user;
    char f[1];
    auto status = db->Get(leveldb::ReadOptions(), user.name, &value);

    // cout<<"sec="<<user.fd<<endl;
    if (status.ok())
    {
        cout << "已经注册！" << endl;
        f[0] = '0';
    }
    else
    {
        // cout << j << endl;
        db->Put(leveldb::WriteOptions(), user.name, j.dump()); //初始化个人表
        jjjson::Friend fri;
        json m = fri;
        fri.from = "";
        fri.to = "";
        string s = "friend";
        s += user.name;
        db->Put(leveldb::WriteOptions(), s, m.dump()); //初始化朋友表

        s = "mygroup";
        s += user.name;
        jjjson::myGroup g;
        g.mygroup.clear();
        g.status.clear();
        m = g;
        db->Put(leveldb::WriteOptions(), s, m.dump());
        db->Get(leveldb::ReadOptions(), s, &value);
        f[0] = '1';

        s = "mymessage";
        s += user.name;
        jjjson::mymessage mes;
        mes.mes.clear();
        j = mes;
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }

    write(user.fd, f, 1);
}

void Login(jjjson::usr user)
{
    string value;
    char f[1];
    auto status = db->Get(leveldb::ReadOptions(), user.name, &value);
    if (status.ok())
    {
        auto j = json::parse(value);
        auto tmp = j.get<jjjson::usr>();
        // if(tmp.status==1)
        //{
        //   f[0]='6';
        //  write(user.fd, f, 1);
        //  return;

        //}
        if (user.pwd == tmp.pwd) //成功
        {
            f[0] = '1';
            user.buf.clear();
            user.time = 0;
            tmp.status = 1;
            tmp.fd = tmpfd;
            j = tmp;
            // cout << j << endl;
            db->Delete(leveldb::WriteOptions(), user.name);
            db->Put(leveldb::WriteOptions(), user.name, j.dump());
        }
        else
            f[0] = '2'; //密码错误
    }
    else
    {
        f[0] = '0'; //用户不存在
    }
    write(user.fd, f, 1);
}

void Find_pwd(jjjson::usr user)
{
    char buf[4096];
    string value;
    db->Get(leveldb::ReadOptions(), user.name, &value);
    json i = json::parse(value);
    auto x = i.get<jjjson::usr>();

    sendMsg(user.fd, value, value.size());
    
    // recv(user.fd,buf,4096,0);
    // string t(buf);
    // cout<<"thisd"<<buf<<endl;
    // json j=json::parse(t);
    // auto y=j.get<jjjson::usr>();
    // if(x.answer==y.answer)
    //{
    //    user.pwd=x.pwd;
    // }
    // else
    // {
    // user.pwd="";
    //}
    // j=user;
    // t=j.dump();
    // send(user.fd,t.c_str(),t.size(),0);
}
void True_pwd(jjjson::usr user)
{
    json j;
    string t;
    char buf[4096];
    string value;
    db->Get(leveldb::ReadOptions(), user.name, &value);
    json i = json::parse(value);
    auto x = i.get<jjjson::usr>();
    if (user.answer == x.answer)
    {
        user.pwd = x.pwd;
    }
    else
    {
        user.pwd.clear();
    }
    j = user;
    t = j.dump();
    sendMsg(user.fd, t, t.size());
}



void Settings(jjjson::usr user)
{
    json j = user;
    char f[1];
    string value;
    string s = j.dump();
    // cout << j << endl;
    db->Get(leveldb::ReadOptions(), user.name, &value);
    json k = json::parse(value);
    auto tmp = k.get<jjjson::usr>();
    db->Delete(leveldb::WriteOptions(), user.name);
    tmp.name = user.name;
    tmp.answer = user.answer;
    tmp.question = user.question;
    tmp.pwd = user.pwd;
    k = tmp;
    auto status = db->Put(leveldb::WriteOptions(), user.name, k.dump());
    if (status.ok())
    {
        f[0] = '1';
    }
    else
        f[0] = '0';
    string x(f);
    sendMsg(user.fd, x, x.size());
}

