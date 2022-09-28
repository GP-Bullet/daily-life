#include"allinclude.h"
#include"ser_log.cpp"


void Build_create(jjjson::usr user)
{
    char f[1];
    string value;
    string s = "group";
    s += user.group;
    cout << s << endl;
    auto status = db->Get(leveldb::ReadOptions(), s, &value);
    if (!status.ok())
    {
        f[0] = '1';
        jjjson::Group g;
        g.owner = user.name;
        g.manager.push_back(user.name);
        g.member.push_back(user.name);
        g.join_req.clear();
        json k = g;
        db->Put(leveldb::WriteOptions(), s, k.dump()); //建群信息表

        s.clear();
        s = "mygroup";
        s += user.name;
        db->Get(leveldb::ReadOptions(), s, &value);
        cout << "firstgroup" << endl;
        k = json::parse(value);
        auto my_group = k.get<jjjson::myGroup>();
        my_group.mygroup.push_back(user.group);
        my_group.status[user.group] = 1; //群主
        k = my_group;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, k.dump()); //个人的群表

        json j;
        s = "group_chat"; //建群聊表
        s += user.group;
        s += user.name;
        jjjson::Gro_chat gc;
        j = gc;
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }
    else
    {
        f[0] = '0';
    }

    string x(f);
    sendMsg(user.fd, x, x.size());
}

void Join_group(jjjson::usr user)
{
    string value;
    json j;
    string s = "group";
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Group>();
    tmp.join_req.push_back(user.name);
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    for (auto it = tmp.manager.begin(); it != tmp.manager.end(); it++)
    {   pthread_mutex_lock(&mutexx);
        s = "mymessage" + *it;
        db->Get(leveldb::ReadOptions(), s, &value); //放到消息列表
        j = json::parse(value);
        auto q = j.get<jjjson::mymessage>();
        char buf[4096];
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s want to  enter %s", user.name.c_str(), user.group.c_str());
        q.mes.push_back(buf);
        j = q;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);
    }
}

void Deal_group_req(jjjson::usr user)
{

    if (user.choice == "agree_group")
    {
        string value;
        json j;
        string s = "group";
        s += user.group;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto tmp = j.get<jjjson::Group>();
        tmp.member.push_back(user.friendname);
        for (auto it = tmp.join_req.begin(); it != tmp.join_req.end(); it++)
        {
            if (*it == user.friendname)
            {
                tmp.join_req.erase(it);
                break;
            }
        }
        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());

        s = "mygroup"; //建我的群表
        s += user.friendname;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        cout << "this " << j << endl;
        auto t = j.get<jjjson::myGroup>();
        t.mygroup.push_back(user.group);
        t.status[user.group] = 3;
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        
         pthread_mutex_lock(&mutexx);
        s = "mymessage" + user.friendname;
        db->Get(leveldb::ReadOptions(), s, &value); //放到消息列表
        j = json::parse(value);
        auto q = j.get<jjjson::mymessage>();
        char buf[4096];
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s accept  you to enter %s", user.name.c_str(), user.group.c_str());
        q.mes.push_back(buf);
        j = q;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);

        s = "group_chat"; //建群聊表
        s += user.group;
        s += user.friendname;
        jjjson::Gro_chat gc;
        j = gc;
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }

    else if (user.choice == "reject_group")
    {
        string value;
        json j;
        string s = "group";
        s += user.group;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto tmp = j.get<jjjson::Group>();
        for (auto it = tmp.join_req.begin(); it != tmp.join_req.end(); it++)
        {
            if (*it == user.name)
            {
                tmp.join_req.erase(it);
                break;
            }
        }
        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());

        db->Get(leveldb::ReadOptions(), user.friendname, &value); //放到消息列表
        j = json::parse(value);
        auto q = j.get<jjjson::usr>();
        char buf[4096];
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s reject  you to enter %s", user.name.c_str(), user.group.c_str());
        q.box.push_back(buf);
        j = q;
        db->Delete(leveldb::WriteOptions(), user.friendname);
        db->Put(leveldb::WriteOptions(), user.friendname, j.dump());
    }
}

void Set_manager(jjjson::usr user)
{
    cout << "1" << endl;
    if (user.choice == "set_manager")
    {
        string s;
        string value;
        json j;
        s = "group";
        s += user.group;
        cout << "hi" << s << endl;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto tmp = j.get<jjjson::Group>();
        tmp.manager.push_back(user.friendname);
        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        s.clear();
        s = "mygroup";
        s += user.friendname;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        // cout<<"佛"<<s<<endl;
        // cout<<j<<endl;
        auto t = j.get<jjjson::myGroup>();
        t.status[user.group] = 2;
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());

         pthread_mutex_lock(&mutexx);
        s = "mymessage" + user.friendname;
        char buf[4096];
        memset(buf, 0, 4096);
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto p = j.get<jjjson::mymessage>();
        sprintf(buf, "%s set you become manager!\n", user.name.c_str());
        p.mes.push_back(buf);
        j = p;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);
    }
    else if (user.choice == "canel_manager")
    {
        string s;
        string value;
        json j;
        s = "group";
        s += user.group;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto tmp = j.get<jjjson::Group>();
        for (auto it = tmp.manager.begin(); it != tmp.manager.end(); it++)
        {
            if (*it == user.friendname)
            {
                tmp.manager.erase(it);
                break;
            }
        }

        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        value.clear();
        s.clear();
        s = "mygroup";
        s += user.friendname;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        // cout<<"佛挡杀佛法是"<<s<<endl;
        // cout<<value<<endl;
        auto t = j.get<jjjson::myGroup>();
        t.status[user.group] = 3;
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());

         pthread_mutex_lock(&mutexx);
        s = "mymessage" + user.friendname;
        char buf[4096];
        memset(buf, 0, 4096);
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto p = j.get<jjjson::mymessage>();
        sprintf(buf, "%s canel your manager!\n", user.name.c_str());
        p.mes.push_back(buf);
        j = p;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);
    }
}

void Kick_sb(jjjson::usr user)
{
    string value;
    string s;
    json j;
    s = "group";
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Group>();
    for (auto it = tmp.member.begin(); it != tmp.member.end(); it++)
    {
        if (*it == user.friendname)
        {
            tmp.member.erase(it);
            break;
        }
    }
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    s = "mygroup";
    s += user.friendname;
    db->Get(leveldb::ReadOptions(), s, &value);
    cout << "mygroup" << value << endl;
    j = json::parse(value);
    auto tq = j.get<jjjson::myGroup>();
    for (auto it = tq.mygroup.begin(); it != tq.mygroup.end(); it++)
    {
        if (*it == user.group)
        {
            tq.mygroup.erase(it);
            break;
        }
    }
    j = tq;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    pthread_mutex_lock(&mutexx);
    s = "mymessage" + user.friendname;
    char buf[4096];
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto t = j.get<jjjson::mymessage>();
    sprintf(buf, "%s already kick you from group : %s", user.name.c_str(), user.group.c_str());
    t.mes.push_back(buf);
    j = t;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    pthread_mutex_unlock(&mutexx);
}



void Look_g(jjjson::usr user)
{
    char f[1];
    string value;
    string s = "group";
    s += user.group;
    cout << s << endl;
    auto status = db->Get(leveldb::ReadOptions(), s, &value);
    if (!status.ok()) //群不存在
    {
        f[0] = '1';
    }
    else
    {
        f[0] = '0';
        cout << value << endl;
        json j = json::parse(value);
        auto tmp = j.get<jjjson::Group>();
        for (auto it = tmp.join_req.begin(); it != tmp.join_req.end(); it++) //发送过请求
        {
            if (*it == user.name)
            {
                f[0] = '3';
                break;
            }
        }
        for (auto it = tmp.member.begin(); it != tmp.member.end(); it++) //已经是群成员
        {
            if (*it == user.name)
            {
                f[0] = '4';
                break;
            }
        }
        for (auto it = tmp.manager.begin(); it != tmp.manager.end(); it++) //已经是群管理
        {
            if (*it == user.name)
            {
                f[0] = '5';
                break;
            }
        }
        if (tmp.owner == user.name)
        {
            f[0] = '6';
        }
    }
    cout << "f:" << f << endl;
    string x(f);
    cout << "x:" << x << endl;
    sendMsg(user.fd, x, x.size());
}



void Offline_mes_gro(jjjson::usr user)
{
    string value;
    json j;
    string s = "group_chat";
    s += user.group;
    s += user.name;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Gro_chat>();
    if (!tmp.unread_mes.empty())
    {
        sendMsg(user.fd, value, value.size());
        tmp.unread_mes.clear();
        tmp.unread_t.clear();
        j = tmp;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }
}

void Chat_group(jjjson::usr user)
{
    string v;
    json j;
    db->Get(leveldb::ReadOptions(), user.name, &v);
    j = json::parse(v);
    auto tmp = j.get<jjjson::usr>();
    tmp.choice = "chat_group";
    tmp.group = user.group;
    j = tmp;
    db->Delete(leveldb::WriteOptions(), user.name);
    db->Put(leveldb::WriteOptions(), user.name, j.dump());
    if (user.mes_fri == "quit")
    {
        string buf = "quit";
        db->Get(leveldb::ReadOptions(), user.name, &v);
        j = json::parse(v);
        auto tmp = j.get<jjjson::usr>();
        tmp.choice = "";
        tmp.group.clear();
        j = tmp;
        db->Delete(leveldb::WriteOptions(), user.name);
        db->Put(leveldb::WriteOptions(), user.name, j.dump());

        sendMsg(user.fd, buf, buf.size());
        return;
    }
    else if ((user.mes_fri == ""))
    {
        cout << "start" << endl;
        Offline_mes_gro(user);
        return;
    }
    string s = "group";
    string value;
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto t = j.get<jjjson::Group>();
    if (t.history.size() > 30) // 超过50条消息就把前面的删了
    {
        t.history.erase(t.history.begin());
        t.history.push_back(user.mes_fri);
        t.time.erase(t.time.begin());
        t.time.push_back(user.time);
    }
    else
    {
        t.history.push_back(user.mes_fri);
        t.time.push_back(user.time);
    }
    j = t;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());

    for (auto it = t.member.begin(); it != t.member.end(); it++)
    {
        if (*it == user.name)
            continue;
        string r;
        string ss = "group_chat";
        ss += user.group;
        ss += *it;
        db->Get(leveldb::ReadOptions(), ss, &r);
        j = json::parse(r);
        auto u = j.get<jjjson::Gro_chat>();
        u.unread_mes.push_back(user.mes_fri);
        u.unread_t.push_back(user.time);
        j = u;
        db->Delete(leveldb::WriteOptions(), ss);
        db->Put(leveldb::WriteOptions(), ss, j.dump());

        string m;
        db->Get(leveldb::ReadOptions(), *it, &m);
        json k = json::parse(m);
        auto y = k.get<jjjson::usr>();
        if (y.choice == "chat_group" && y.group == user.group)
        {
            string r;
            string ss = "group_chat";
            ss += user.group;
            ss += *it;
            db->Get(leveldb::ReadOptions(), ss, &r);
            sendMsg(y.fd, r, r.size());
            cout << "myfd" << y.fd << endl;
            j = json::parse(r);
            auto u = j.get<jjjson::Gro_chat>();
            u.unread_mes.clear();
            u.unread_t.clear();
            j = u;
            db->Delete(leveldb::WriteOptions(), ss);
            db->Put(leveldb::WriteOptions(), ss, j.dump());
        }
        else
        {
            pthread_mutex_lock(&mutexx);
            s = "mymessage" + *it;
            db->Get(leveldb::ReadOptions(), s, &value);
            j = json::parse(value);
            auto c = j.get<jjjson::mymessage>();
            char buf[1000];
            sprintf(buf, "%s send a message from group:%s : %s", user.name.c_str(), user.group.c_str(), user.mes_fri.c_str());
            c.mes.push_back(buf);
            j = c;
            db->Delete(leveldb::WriteOptions(), s);
            db->Put(leveldb::WriteOptions(), s, j.dump());
            pthread_mutex_unlock(&mutexx);
        }
    }
}

void Offline_mes_fri(jjjson::usr user)
{
    string value;
    json j;
    string s = user.name;
    s += user.friendname;
    db->Get(leveldb::ReadOptions(), s, &value);
    sendMsg(user.fd, value, value.size());
    j = json::parse(value);
    auto tmp = j.get<jjjson::Fri_chat>();
    tmp.unread.clear();
    tmp.unread_t.clear();
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
}

void Check_group_history(jjjson::usr user)
{
    string value;
    string s = "group";
    json j;
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    sendMsg(user.fd, value, value.size());
}

void *R_file(void *arg)
{
    pthread_detach(pthread_self());
    last_choice = "recv_file_fri";
    long long tmplen = 0;
    long long ret = 0;
    long long ret2 = 0;
    cout << last_path << endl;
    int fd = open(last_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
    char buff[4096];
    memset(buff, 0, 4096);

    while (1)
    {

        ret2 = recv(last_fd, buff, 4096, 0);
        // cout<<errno<<endl;

        // if(tmplen+ret2>last_len){
        //     ret2=last_len-tmplen;
        // }
        // cout<<ret2<<endl;
        //  cout << buf << endl;
        //  if (strcmp(buf, "over") == 0)
        //  {
        //      cout << "over" << endl;
        //      last_choice = "";
        //      break;
        //  }

        // if(ret<4096)
        // buf[ret]='\0';

        ret = write(fd, buff, ret2);
        if (ret > 0)
            tmplen += ret;
        cout << tmplen << endl;
        cout << last_len << endl;
        if (tmplen >= last_len)
        {
            last_choice = "";
            break;
        }
    }

    close(fd);
    return NULL;
}

void Recv_file_fri(jjjson::usr user)
{
    pthread_t tid;
    last_fd = user.fd;
    last_len = user.id;
    string path = "/home/chenzhenxxx/chatroom/" + user.filename;
    last_path = path;
    string value;
    json j;
    string s = user.friendname;
    s += user.name;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Fri_chat>();
    tmp.file.push_back(user.filename);
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    
    char buf[200];
    pthread_mutex_lock(&mutexx);
    s = "mymessage" + user.friendname;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto ta = j.get<jjjson::mymessage>();
    sprintf(buf, "%s send a file: %s to you", user.name.c_str(), user.filename.c_str());
    string t(buf);
    ta.mes.push_back(t);
    j = ta;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    pthread_mutex_unlock(&mutexx);
    pthread_create(&tid, NULL, R_file, NULL);
}

void Send_file_fri(jjjson::usr user)
{
    long long ret = 0, sum = 0;
    long long retw = 0;
    string path = "/home/chenzhenxxx/chatroom/" + user.filename;
    int fd;
    if ((fd = open(path.c_str(), O_RDONLY)) < 0)
    {
        close(fd);
        cout << "open error" << endl;
        return;
    }
    char x[4096];
    memset(x, 0, 4096);
    struct stat st;
    lstat(path.c_str(), &st);
    while (1)
    {
        ret = read(fd, x, 4096);

        // x[ret] = '\0';

        // cout << x << endl;
        // cout << ret << endl;
        // cout << strlen(x) << endl;

        retw = send(user.fd, x, ret,0);
        if (retw > 0)
            sum += retw;
        memset(x, 0, 4096);
        if (ret > retw)
        {
            lseek(fd, sum, SEEK_SET);
        }
        if (sum >= st.st_size)
        {

            break;
        }
    }

   
    string value;
    json j;
    string s = user.name;
    s += user.friendname;
   
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Fri_chat>();
    for (auto it = tmp.file.begin(); it != tmp.file.end(); it++)
    {
        if (*it == user.filename)
        {
            tmp.file.erase(it);
            break;
        }
    }
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    cout << "good" << endl;

    close(fd);
}

void Recv_file_gro(jjjson::usr user)
{
    last_choice = "recv_file_gro";
    last_fd = user.fd;
    last_len = user.id;
    json j;
    string value;
    string s;
    char buf[4096];
    s = "group";
    s += user.group;
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Group>();
    for (auto it = tmp.member.begin(); it != tmp.member.end(); it++)
    {
        if (*it == user.name)
            continue;
        
        pthread_mutex_lock(&mutexx);
        s = "mymessage" + *it;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto t = j.get<jjjson::mymessage>();
        sprintf(buf, "in group :%s :%s send a file: %s to you ", user.group.c_str(), user.name.c_str(), user.filename.c_str());
        t.mes.push_back(buf);
        j = t;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
        pthread_mutex_unlock(&mutexx);

        s = "group_chat";
        s += user.group;
        s += *it;
        db->Get(leveldb::ReadOptions(), s, &value);
        j = json::parse(value);
        auto y = j.get<jjjson::Gro_chat>();
        y.filename.push_back(user.filename);
        j = y;
        db->Delete(leveldb::WriteOptions(), s);
        db->Put(leveldb::WriteOptions(), s, j.dump());
    }

    string path = "/home/chenzhenxxx/chatroom/" + user.filename;
    last_path = path;
    pthread_create(&tid, NULL, R_file, NULL);
}

void Send_file_gro(jjjson ::usr user)
{
    string path = "/home/chenzhenxxx/chatroom/" + user.filename;
    int fd;
    if ((fd = open(path.c_str(), O_RDONLY)) < 0)
    {
        close(fd);
        cout << "open error" << endl;
        return;
    }
    long long ret = 0, sum = 0, retw = 0;
    char x[4096];
    memset(x, 0, 4096);
    struct stat st;
    lstat(path.c_str(), &st);
    while (1)
    {
        ret = read(fd, x, 4096);

        // x[ret] = '\0';

        // cout << x << endl;
        // cout << ret << endl;
        // cout << strlen(x) << endl;

        retw = send(user.fd, x, ret,0);
        if (retw > 0)
            sum += retw;
        memset(x, 0, 4096);
        if (ret > retw)
        {
            lseek(fd, sum, SEEK_SET);
        }
        if (sum >= st.st_size)
        {

            break;
        }
    }

    
    string value;
    json j;
    string s = "group_chat";
    s += user.group;
    s += user.name;
    
    db->Get(leveldb::ReadOptions(), s, &value);
    j = json::parse(value);
    auto tmp = j.get<jjjson::Gro_chat>();
    for (auto it = tmp.filename.begin(); it != tmp.filename.end(); it++)
    {
        if (*it == user.filename)
        {
            tmp.filename.erase(it);
            break;
        }
    }
    j = tmp;
    db->Delete(leveldb::WriteOptions(), s);
    db->Put(leveldb::WriteOptions(), s, j.dump());
    cout << "good" << endl;

    close(fd);
}

void *Inform(void *arg)
{
    pthread_detach(pthread_self());
    jjjson::usr user = *(jjjson::usr *)arg;
    string s = "mymessage" + user.name;
    cout << user.fd << endl;
    cout << s << endl;

    while (1)
    {
        
        string value;
        value.clear();
        pthread_mutex_lock(&mutexx);
        auto status = db->Get(leveldb::ReadOptions(), s, &value);
        // cout<<"ha"<<value<<endl;
        json j = json::parse(value);
        auto tmp = j.get<jjjson::mymessage>();

        if (tmp.mes.size() != 0)
        {
            // cout<<tmp.mes.size()<<endl;
            auto it = tmp.mes.begin();
            sendMsg(user.fd, (*it), (*it).size());
            tmp.mes.erase(tmp.mes.begin());
            // send(user.fd, value.c_str(), value.size(), 0);
            // tmp.mes.clear();
            j = tmp;
            db->Delete(leveldb::WriteOptions(), s);
            db->Put(leveldb::WriteOptions(), s, j.dump());
            // break;
            if(*it=="exit")
            { pthread_mutex_unlock(&mutexx);
              break;
            }
        }
        pthread_mutex_unlock(&mutexx);
    }
    return NULL;
}