#include"allinclude.h"
#include"ser_log.cpp"

void Add_friend(jjjson::usr user)
{
    string value;
    string s = "friend";
    s += user.friendname;
    auto status = db->Get(leveldb::ReadOptions(), s, &value);
    auto j = json::parse(value);
    auto fri = j.get<jjjson::Friend>();
    fri.request.push_back(user.name);
    j = fri;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    pthread_mutex_lock(&mutexx);
    s = "mymessage" + user.friendname;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::mymessage>();
    char buf[4096];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s want to become your friend", user.name.c_str());
    string t(buf);
    tmp.mes.push_back(t);
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
     pthread_mutex_unlock(&mutexx);
}

void Deal_friendreq(jjjson::usr user)
{
    if (user.choice == "agree_friend")
    {
        string value;
        string s = "friend";
        s += user.name;
        auto status = db->Get(leveldb::ReadOptions(), s, &value);
        auto j = json::parse(value);
        auto fri = j.get<jjjson::Friend>();
        for (auto iter = fri.request.begin(); iter != fri.request.end(); iter++) //删申请
        {
            if (*iter == user.friendname)
            {
                fri.request.erase(iter);
                break;
            }
        }

        //加到好友列表
        fri.myfri.push_back(user.friendname);
        fri.ship[user.friendname] = 0;
        j = fri;
        string tmp = j.dump();
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, tmp);

        s = "friend";
        s += user.friendname;
        db->Get(leveldb::ReadOptions(), s, &tmp); //对方的添加
        j = json::parse(tmp);
        auto fri1 = j.get<jjjson::Friend>();
        fri1.myfri.push_back(user.name);
        fri1.ship[user.name] = 0;
        j = fri1;
        tmp = j.dump();
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, tmp);

        pthread_mutex_lock(&mutexx);
        s = "mymessage" + user.friendname;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto t = j.get<jjjson::mymessage>();
        char buf[4096];
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s accept to become your friend", user.name.c_str());
        t.mes.push_back(buf);
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);

        //创建两个朋友消息表
        s = user.name;
        s += user.friendname;
        jjjson::Fri_chat chat;
        json k = chat;
        db->Put(leveldb::WriteOptions(), s, k.dump());
        s = user.friendname;
        s += user.name;
        k = chat;
        db->Put(leveldb::WriteOptions(), s, k.dump());
    }
    else if (user.choice == "reject_friend")
    {
        string value;
        string s = "friend";
        s += user.name;
        auto status = db->Get(leveldb::ReadOptions(), s, &value);
        auto j = json::parse(value);
        auto fri = j.get<jjjson::Friend>();
        for (auto iter = fri.request.begin(); iter != fri.request.end(); iter++) //删申请
        {
            if (*iter == user.friendname)
            {
                fri.request.erase(iter);
                break;
            }
        }
        j = fri;
        string tmp = j.dump();
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, tmp);

        db->Get(leveldb::ReadOptions(), user.friendname, &value);
        j = json::parse(value);
        auto t = j.get<jjjson::usr>();
        char b[4096];
        memset(b, 0, sizeof(b));
        sprintf(b, "%s reject to become your friend", user.name.c_str());
        t.box.push_back(b);
        j = t;
        db->Delete(leveldb::WriteOptions(), user.friendname);
        db->Put(leveldb::WriteOptions(), user.friendname, j.dump());
    }
}

void Check_friend(jjjson::usr user)
{
    string value;
    char f[1];
    // cout<<"lala"<<user.friendname<<endl;
    auto status = db->Get(leveldb::ReadOptions(), user.friendname, &value);
    if (!status.ok()) //没有此人
    {
        f[0] = '0';
        string x(f);
        sendMsg(user.fd, x, x.size());
        return;
    }
    string s = "friend";
    s += user.friendname;
    status = db->Get(leveldb::ReadOptions(), s, &value);
    json j = json::parse(value);
    auto myfriend = j.get<jjjson::Friend>();

    for (auto iter = myfriend.myfri.begin(); iter != myfriend.myfri.end(); iter++) //已是朋友
    {
        if (*iter == user.name)
        {
            f[0] = '3';
            string x(f);
            sendMsg(user.fd, x, x.size());
            return;
        }
    }

    for (auto iter = myfriend.request.begin(); iter != myfriend.request.end(); iter++) //发过请求
    {
        if (*iter == user.name)
        {
            f[0] = '2';
            string x(f);
            sendMsg(user.fd, x, x.size());
            return;
        }
    }
    if (f[0] != '0' && f[0] != '2' && f[0] != '3')
    {
        f[0] = '1';
        string x(f);
        sendMsg(user.fd, x, x.size());

        // Add_friend(user);
        return;
    }
}
void add_friend(jjjson::usr user)
{
    string value;
    char f[1];
    // cout<<"lala"<<user.friendname<<endl;
    auto status = db->Get(leveldb::ReadOptions(), user.friendname, &value);
    if (!status.ok()) //没有此人
    {
        f[0] = '0';
        string x(f);
        sendMsg(user.fd, x, x.size());
        return;
    }
    string s = "friend";
    s += user.friendname;
    status = db->Get(leveldb::ReadOptions(), s, &value);
    json j = json::parse(value);
    auto myfriend = j.get<jjjson::Friend>();

    for (auto iter = myfriend.myfri.begin(); iter != myfriend.myfri.end(); iter++) //已是朋友
    {
        if (*iter == user.name)
        {
            f[0] = '3';
            string x(f);
            sendMsg(user.fd, x, x.size());
            return;
        }
    }

    for (auto iter = myfriend.request.begin(); iter != myfriend.request.end(); iter++) //发过请求
    {
        if (*iter == user.name)
        {
            f[0] = '2';
            string x(f);
            sendMsg(user.fd, x, x.size());
            return;
        }
    }
    if (f[0] != '0' && f[0] != '2' && f[0] != '3')
    {
        f[0] = '1';
        string x(f);
        sendMsg(user.fd, x, x.size());

        Add_friend(user);
        return;
    }
}

void Delete_fri(jjjson::usr user)
{
    char f[1];
    string s = "friend";
    s += user.name;
    string value;
    auto status = db->Get(leveldb::ReadOptions(), s, &value);
    json j = json::parse(value);
    auto tmp1 = j.get<jjjson::Friend>();
    for (auto it = tmp1.myfri.begin(); it != tmp1.myfri.end(); it++) //删自己的好友列表
    {
        if (*it == user.friendname)
        {
            tmp1.myfri.erase(it);
            break;
        }
    }
    j = tmp1;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    s = "friend";
    s += user.friendname;
    status = db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp2 = j.get<jjjson::Friend>();
    for (auto it = tmp2.myfri.begin(); it != tmp2.myfri.end(); it++) //删自己的好友列表
    {
        if (*it == user.name)
        {
            tmp2.myfri.erase(it);
            break;
        }
    }
    j = tmp2;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

     pthread_mutex_lock(&mutexx);
    s = "mymessage" + user.friendname;
    status = db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp3 = j.get<jjjson::mymessage>();
    char buf[4096];
    sprintf(buf, "%s delete you!", user.name.c_str());
    tmp3.mes.push_back(buf);
    j = tmp3;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    pthread_mutex_unlock(&mutexx);
    string x = "1";
    sendMsg(user.fd, x, x.size());
}

void Chat_sb(jjjson::usr user)
{
    string value;
    string v;
    json j;
    db->Get(leveldb::ReadOptions(), user.name, &v);
    j = json::parse(v);
    
    auto m = j.get<jjjson::usr>();
    m.choice = "chat_sb";
    m.friendname = user.friendname;
    j = m;
    db->Delete(leveldb::WriteOptions(), user.name);
    db->Put(leveldb::WriteOptions(), user.name, j.dump());
    if (user.mes_fri == "")
        return;
    if (user.mes_fri == "quit")
    {
        string buf = "quit";
        db->Get(leveldb::ReadOptions(), user.name, &v);
        j = json::parse(v);
        auto tmp = j.get<jjjson::usr>();
        tmp.choice = "";
        tmp.friendname.clear();
        j = tmp;
        db->Delete(leveldb::WriteOptions(), user.name);
        db->Put(leveldb::WriteOptions(), user.name, j.dump());

        sendMsg(user.fd, buf, buf.size());
        return;
    }
    string s = user.friendname;
    s += user.name;
    // printf("1\n");
    db->Get(leveldb::ReadOptions(), s, &value); //先放到对方的未读消息并存到对方的消息记录
                                                // cout << "valie:" << value << endl;
    j = json::parse(value);
    
    
    // printf("*****\n");
    auto mp = j.get<jjjson::Fri_chat>();
    // cout << "Jj" << j << endl;
    string h;
    h = user.name + " :" + user.mes_fri;
    if (mp.history.size() > 20) // 超过50条消息就把前面的删了
    {
        mp.history.erase(mp.history.begin());
        mp.history.push_back(h);
        mp.time.erase(mp.time.begin());
        mp.time.push_back(user.time);
    }
    else
    {
        mp.history.push_back(h);
        mp.time.push_back(user.time);
    }
    mp.unread.push_back(user.mes_fri);
    mp.unread_t.push_back(user.time);
    j = mp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    s = user.name;
    s += user.friendname;
    cout<<"table"<<s<<endl;
    db->Get(leveldb::ReadOptions(), s, &value); //放到自己的消息记录
    j = json::parse(value);
    auto t = j.get<jjjson::Fri_chat>();
    if (t.history.size() > 20) // 超过50条消息就把前面的删了
    {
        t.history.erase(t.history.begin());
        t.history.push_back(h);
        t.time.erase(t.time.begin());
        t.time.push_back(user.time);
    }
    else
    {
        t.history.push_back(h);
        t.time.push_back(user.time);
    }
    j = t;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    db->Get(leveldb::ReadOptions(), user.friendname, &value);
    j = json::parse(value);
    auto i = j.get<jjjson::usr>();
    if (i.friendname != user.name || i.choice != "chat_sb")
    {
        pthread_mutex_lock(&mutexx);
        char buf[200];
        sprintf(buf, "%s say to you : %s", user.name.c_str(), user.mes_fri.c_str());
        string t(buf);
        string dfg = "mymessage" + user.friendname;
        string op;
        db->Get(leveldb::ReadOptions(), dfg, &op);
        j = json::parse(op);
        cout<<"6"<<endl;
        auto hh = j.get<jjjson::mymessage>();

        hh.mes.push_back(t);
        j = hh;
        db->Delete(leveldb::WriteOptions(), dfg);
        db->Put(leveldb::WriteOptions(), dfg, j.dump());
        pthread_mutex_unlock(&mutexx);
    }
    else
    {
        string h = user.friendname;
        h += user.name;
        db->Get(leveldb::ReadOptions(), h, &value);
        j = json::parse(value);
        cout<<"7"<<endl;
        auto f = j.get<jjjson::Fri_chat>();
        sendMsg(i.fd, value, value.size());
        f.unread.clear();
        f.unread_t.clear();
        j = f;
        db->Delete(leveldb::WriteOptions(), h);
        db->Put(leveldb::WriteOptions(), h, j.dump());
    }
}

void *Recv_mes(void *arg)
{
    pthread_detach(pthread_self());
    string value;
    jjjson::usr user = *(jjjson::usr *)arg;
    string s = user.name;
    s += user.friendname;
    while (1)
    {
        string qq;
        db->Get(leveldb::ReadOptions(), user.name, &qq);
        json k = json::parse(qq);
        auto dd = k.get<jjjson::usr>();

        if (dd.mes_fri == "quit")
        {
            printf("over %d\n", user.fd);
            // char buf[20]="quit";
            // cout<<user.fd<<endl;
            
            // send(user.fd,buf,20,0);
            break;
        }

        // printf("000\n");
        db->Get(leveldb::ReadOptions(), s, &value);
        json j = json::parse(value);
        string t = j.dump();
        auto q = j.get<jjjson::Fri_chat>();
        auto p = q;
        string b;
        db->Get(leveldb::ReadOptions(), user.friendname, &b);
        json g = json::parse(b);
        auto x = g.get<jjjson::usr>();
        db->Get(leveldb::ReadOptions(), user.name, &b);
        g = json::parse(b);
        auto y = g.get<jjjson::usr>();
        // cout<<"ss"<<x.choice<<endl;
        // cout<<x.friendname<<endl;
        if ((q.unread.size() != 0) && x.name == y.friendname && y.choice == "chat_sb")
        {
            sendMsg(user.fd, t, t.size());
            q.unread.clear();
            q.unread_t.clear();
            j = q;
            db->Delete(leveldb::WriteOptions(), s);
            db->Put(leveldb::WriteOptions(), s, j.dump());
        }

        // for(auto it=p.unread.begin();it!=p.unread.end();it++)
        //{
        // if(*it=="quit")
        // printf("over %d\n",user.fd);
        // char buf[20]="quit";
        // break;
        //}

        // pthread_mutex_unlock(&mutexx);
    }
    return NULL;
}

void Check_history(jjjson::usr user)
{
    string s = user.name;
    s += user.friendname;
    string value;
    db->Get(leveldb::ReadOptions(), s, &value);
    json j = json::parse(value);
    string t = j.dump();
    // cout<<"hello"<<t<<endl;
    sendMsg(user.fd, t, t.size());
}

void Shield_fri(jjjson::usr user)
{

    string value; //自己的
    string s = "friend";
    s += user.name;
    db->Get(leveldb::ReadOptions(), s, &value);

    // cout<<"myvla"<<value<<endl;

    json j = json::parse(value);
    auto tmp = j.get<jjjson::Friend>();
    if (user.choice == "start_shield")
    {
        tmp.ship[user.friendname] = 1;
    }
    else
    {
        tmp.ship[user.friendname] = 0;
    }
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    s = "friend"; //好友的
    s += user.friendname;
    db->Get(leveldb::ReadOptions(), s, &value);

    // cout<<"otttvla"<<value<<endl;

    j = json::parse(value);
    tmp = j.get<jjjson::Friend>();
    if (user.choice == "start_shield")
    {
        tmp.ship[user.name] = 1;
    }
    else
    {
        tmp.ship[user.name] = 0;
    }
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    // db->Get(leveldb::ReadOptions(),s,&value);
    // cout<<"ans"<<value<<endl;
}