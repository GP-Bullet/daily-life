#pragma once
#include "allinclude.h"
#include"cli_recv.cpp"
#include"cli_log.cpp"

int cfd;
#define SIZE 200000
#define LOGSLEEP 150000
#define LOGSLEEP2 7000
//把代码分开
//把光标移动到框里面输入
//点赞   表情    短信



void Build_group(jjjson::usr user)
{
  char *f;
  cout << "请输入想要创建的群" << endl;
  cin >> user.group;
  user.choice = "build_group";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] == '1')
  {
    cout << "创建成功" << endl;
  }
  else
  {
    cout << "该群已经创建" << endl;
  }
  free(f);
}

void Join_group(jjjson::usr user)
{
  char *f;
  cout << "请输入想加入的群聊" << endl;
  cin >> user.group;
  user.choice = "look_g";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] == '1')
  {
    cout << "该群不存在" << endl;
  }
  else if (f[0] == '0')
  {
    user.choice = "join_group";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
    cout << "成功发送请求" << endl;
  }
  else if (f[0] == '3')
  {
    cout << "已经发送过请求，请勿重复发送！" << endl;
  }
  else if (f[0] == '4')
  {
    cout << "已经是群成员" << endl;
  }
  free(f);
}

void deal_group_req(jjjson::usr user)
{
  int flag = 0;
  while (1)
  {
    flag = 0;
    char *buf;
    user.choice = "group_req";
    json j = user;
    string s = j.dump();
    sendMsg(cfd, s, s.size());
    recvMsg(cfd, &buf);
    buf[strlen(buf)] = '\0';
    string tmp(buf);
    free(buf);
    j = json::parse(tmp);

    auto g = j.get<jjjson::Group>();
    if (g.owner == user.name)
    {
      flag = 1;
    }
    for (auto it = g.manager.begin(); it != g.manager.end(); it++)
    {
      if (*it == user.name)
      {
        flag = 1;
      }
    }
    if (flag == 0)
    {
      cout << "你不是管理员或群主！" << endl;
      return;
    }

    for (auto it = g.join_req.begin(); it != g.join_req.end(); it++)
    {
      cout << "from____________" << *it << endl;
    }
    printf("     ***********         welcome %s       **********  \n", user.name.c_str());
    printf("    ***********         1.操作         **********  \n");
    printf("    ***********         2.退出              *************\n");
    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      cout << "请选择操作对象" << endl;
      string s;
      cin >> s;
      printf("    ***********  1.同意     2.拒绝      3.取消         **********  \n");
      int x;
      cin >> x;
      if (x == 1)
        user.choice = "agree_group";
      else if (x == 2)
        user.choice = "reject_group";
      if (x != 3)
      {
        user.friendname = s;
        json j = user;
        string s = j.dump();
        sendMsg(cfd, s, s.size());
      }
      break;
    }
    if (select == 2)
    {
      break;
    }
  }
}

void check_member(jjjson::usr user)
{
  json j;
  string s;
  char *buf;
  user.choice = "check_member";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &buf);
  string t(buf);
  free(buf);
  j = json::parse(t);
  auto tmp = j.get<jjjson::Group>();
  cout << "***********" << user.group << "************" << endl;
  cout << "*******成员*******"
       << "***身份****" << endl;
  cout << "*******" << tmp.owner << "**********owner****" << endl;
  for (auto it = tmp.manager.begin(); it != tmp.manager.end(); it++)
  {
    if (*it != tmp.owner)
      cout << "*******" << *it << "**********manager****" << endl;
  }
  for (auto it = tmp.member.begin(); it != tmp.member.end(); it++)
  {
    int flag = 1;
    if (tmp.owner == *it)
    {
      flag = 0;
      continue;
    }
    for (auto i = tmp.manager.begin(); i != tmp.manager.end(); i++)
    {
      if (*i == *it)
      {
        flag = 0;
        break;
      }
    }
    if (flag == 0)
      continue;
    cout << "*******" << *it << "**********member****" << endl;
  }
}

void set_manager(jjjson::usr user)
{

  char *f;
  json j;
  string s;
  user.choice = "look_g";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] != '6')
  {
    cout << "不是群主，无权操作" << endl;
    free(f);
    return;
  }
  free(f);
  while (1)
  {
    char *ff;
    cout << "******1.添加管理员        2.取消管理员        3.退出******" << endl;
    string select;
    cin >> select;
    if (select == "1")
    {
      string tmpname = user.name;
      cout << "请输入想要添加的管理员" << endl;
      cin >> user.name;
      user.friendname = user.name;
      user.choice = "look_g";
      j = user;
      s = j.dump();
      sendMsg(cfd, s, s.size());
      recvMsg(cfd, &ff);
      user.name = tmpname;
      if (ff[0] != '4' && ff[0] != '5' && ff[0] != '6')
      {
        cout << "不是群成员" << endl;
        free(ff);
        return;
      }
      if (ff[0] == '5' || ff[0] == '6')
      {
        cout << "已是管理员" << endl;
        free(ff);
        return;
      }
      user.choice = "set_manager";
      free(ff);
    }
    else if (select == "2")
    {
      char *fff;
      string tmpname = user.name;
      cout << "请输入想要撤销的管理员" << endl;
      cin >> user.name;
      user.friendname = user.name;
      user.choice = "look_g";
      j = user;
      s = j.dump();
      sendMsg(cfd, s, s.size());
      recvMsg(cfd, &fff);
      user.name = tmpname;
      if (fff[0] != '4' && fff[0] != '5' && fff[0] != '6')
      {
        cout << "不是群成员" << endl;
        free(fff);
        return;
      }
      if ((fff[0] != '5') && (fff[0] != '6'))
      {
        cout << "不是管理员" << endl;
        free(fff);
        return;
      }
      else if (fff[0] == '6')
      {
        cout << "此人是群主无权更改" << endl;
        free(fff);
        return;
      }
      user.choice = "canel_manager";
      free(fff);
    }
    else
    {
      break;
    }
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
  }
}

void kick_sb(jjjson::usr user)
{
  char *f;
  json j;
  string s;
  user.choice = "look_g";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] != '6' && f[0] != '5')
  {
    cout << "不是管理员，无权操作" << endl;
    free(f);
    return;
  }
  free(f);
  while (1)
  {
    check_member(user);

    cout << "*****1.踢人       2.退出*****" << endl;
    string select;
    cin >> select;
    if (select == "1")
    {
      char *ff;
      string tmpname = user.name;
      cout << "请输入想要踢的人" << endl;
      cin >> user.name;
      user.friendname = user.name;
      user.choice = "look_g";
      j = user;
      s = j.dump();
      sendMsg(cfd, s, s.size());
      recvMsg(cfd, &ff);
      user.name = tmpname;
      if (ff[0] != '4' && ff[0] != '5' && ff[0] != '6')
      {
        cout << "不是群成员" << endl;
        free(ff);
        return;
      }
      if (ff[0] == '5' || ff[0] == '6')
      {
        cout << "是管理员，无法踢人" << endl;
        free(ff);
        return;
      }
      free(ff);
      user.choice = "kick_sb";
      j = user;
      s = j.dump();
      sendMsg(cfd, s, s.size());
    }
    else
    {
      break;
    }
  }
}

void withdraw_group(jjjson::usr user)
{
  cout << "请确认你要退出群：" << user.group << endl;
  cout << "*****1.确认       *****2.取消****" << endl;
  string select;
  cin >> select;
  if (select == "1")
  {
    user.choice = "withdraw_group";
    json j;
    string s;
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
  }
  else
  {
    return;
  }
}

void *recv_chat_group(jjjson::usr arg)
{ // pthread_detach(pthread_self());
  // jjjson::usr tmp = arg;
  // tmp.choice = "recv_mes_gro";
  // json j = tmp;
  // string s = j.dump();
  // send(cfd, s.c_str(), s.size(), 0);
  while (1)
  {

    char *buf;

    int ret = recvMsg(cfd, &buf);
    if ((strcmp(buf, "quit")) == 0)
    {
      cout << "gameover" << endl;
      free(buf);
      break;
    }
    else
    {
      string t(buf);
      free(buf);
      // cout<<"khj--"<<t<<endl;
      json j = json::parse(t);
      auto q = j.get<jjjson::Gro_chat>();
      for (auto it = q.unread_mes.begin(); it != q.unread_mes.end(); it++)
      {
        printf("%50c", ' ');
        cout << LIGHT_RED << *it << endl;
        printf("%40c", ' ');
        cout << ctime(&q.unread_t[0]) << NONE << endl;
        q.unread_t.erase(q.unread_t.begin());
      }
    }
  }
  return NULL;
}

void Check__group_history(jjjson::usr user)
{
  json j;
  string s;
  char *buf;
  string value;
  user.choice = "check_group_history";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &buf);
  string t(buf);
  free(buf);
  cout << t << endl;
  j = json::parse(t);
  auto tmp = j.get<jjjson::Group>();
  for (auto it = tmp.history.begin(); it != tmp.history.end(); it++)
  {
    cout << *it << endl;
    cout << ctime(&tmp.time[0]) << endl;
    tmp.time.erase(tmp.time.begin());
  }
}

void chat_group(jjjson::usr user)
{

  cout << "1.开始聊天" << endl;
  cout << "2.查看聊天记录" << endl;
  // cout<<"3.传文件"<<endl;
  // cout<<"4.收文件"<<endl;
  cout << "3.输入其他键退出" << endl;
  string select;
  cin >> select;
  if (select == "1")
  {
    pthread_t tid;
    thread recvv(recv_chat_group, user);
    //  user.choice = "offline_mes_gro"; //获取离线消息
    //  json k = user;
    //  string l = k.dump();
    string l;
    sendMsg(cfd, l, l.size());
    user.choice = "chat_group"; //先唤醒聊天状态
    user.mes_fri = "";
    json j = user;
    l = j.dump();
    sendMsg(cfd, l, l.size());
     cout << "开始聊天吧！";
    getchar();
    while (1)
    {
      string m;
      string s;
      s = "from:" + user.name + ":";
      user.choice = "chat_group";
      getline(cin,m);
      s += m;
      time_t t;
      t = time(NULL);
      user.mes_fri = s;
      user.time = t;
      if (m == "quit")
      {
        user.mes_fri = m;
        // user.choice = "quit_chatgro";
        json j = user;
        string l = j.dump();
        sendMsg(cfd, l, l.size());
        break;
      }
      cout << LIGHT_BLUE << user.name << " :" << s << endl;
      cout << ctime(&t) << NONE << endl;
      json j = user;
      string l = j.dump();
      sendMsg(cfd, l, l.size());
    }
    recvv.join();
  }
  else if (select == "2")
  {
    Check__group_history(user);
  }
}

void send_file_gro(jjjson::usr user)
{ 
  while(1)
  {
  char path[1000], name[100];
  cout << "请输入文件地址(输入0退出)" << endl;
  cin >> path;
  if(strcmp(path,"0")==0)
  {
    break;
  }
  int sign = 0, cnt = 0;
  for (int i = strlen(path) - 1; i >= 0; i--)
  {
    if (path[i] == '/')
    {
      sign = i;
      break;
    }
  }
  for (int j = sign + 1; j < strlen(path); j++)
  {
    name[cnt++] = path[j];
  }
  user.filename = name;
  int fd;
  if ((fd = open(path, O_RDONLY)) < 0)
  {
    cout << "open error" << endl;
    return;
  }
  json j;
  string s;
  int ret = 0;
  user.choice = "recv_file_gro";
  struct stat st;
  stat(path, &st);
  user.id = st.st_size;
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());

  long long retw = 0, sum = 0;
  char x[4096];
  memset(x, 0, 4096);

  while (1)
  {
    ret = read(fd, x, 4096);
    x[ret] = '\0';
    retw = send(cfd, x, ret, 0);
    if (retw > 0)
      sum += retw;

    memset(x, 0, 4096);
    if (ret > retw)
    {
      lseek(fd, sum, SEEK_SET);
    }
    cout << sum << endl;
    cout << st.st_size << endl;
    if (sum >= st.st_size)
    {
      break;
    }
  }

  close(fd);
  }
}

void recv_file_gro(jjjson::usr user)
{
  while (1)
  {
    int fd;
    json j;
    string s;
    int flag = 0;
    user.choice = "check_file_gro";
    char *buf;
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
    recvMsg(cfd, &buf);
    string t(buf);
    free(buf);
    cout << t << endl;
    j = json::parse(t);
    auto x = j.get<jjjson::Gro_chat>();
    for (auto it = x.filename.begin(); it != x.filename.end(); it++)
    {
      cout << "*******" << *it << endl;
    }
    cout << "请选择操作对象(输入0退出)" << endl;
    string q;
    cin >> q;
    if (q == "0")
      break;
    for (auto it = x.filename.begin(); it != x.filename.end(); it++)
    {
      if (q == *it)
      {
        flag = 1;
      }
    }
    if (flag == 0)
    {
      cout << "请选择正确的对象" << endl;
      continue;
    }
    cout << "请选择保存路径" << endl;
    string path;
    cin >> path;
    path += "/";
    path += q;
    cout << path << endl;
    if ((fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
    {
      cout << "create file error" << endl;
      continue;
    }
    long long size = 0;
    long long tmplen = 0;
    user.filename = q;
    user.choice = "file_size";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
    char *bu;
    recvMsg(cfd, &bu);
    string d(bu);
    free(bu);
    j = json::parse(d);
    auto tt = j.get<jjjson::usr>();
    size = tt.id;

    user.filename = q;
    user.choice = "send_file_gro";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());

    long long ret = 0, ret2 = 0;

    while (1)
    {
      char b[4096];
      ret2 = recv(cfd, b, 4096, 0);
      ret = write(fd, b, ret2);
      if (ret > 0)
        tmplen += ret;
      if (tmplen >= size)
      {
        break;
      }

      memset(b, 0, 4096);
    }
    close(fd);
  }
}

void Enter_group(jjjson::usr user)
{
  char *f;
  cout << "请输入进入的群聊（0退出）" << endl;
  cin >> user.group;
  if (user.group == "0")
    return;
  user.choice = "look_g";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
 
  if (f[0] == '1')
  {
    cout << "该群不存在" << endl;
    free(f);
    return;
  }
  else if (f[0] != '4' && f[0] != '6' && f[0] != '5')
  {
    cout << "你不是该群成员" << endl;
    free(f);
    return;
  }
  free(f);
  while (1)
  {
    // Inform(user);
    printf("\033[2;12H ____________________________________________________\n");
    printf("\033[3;12H｜              (^_^)    welcome %s                  ｜\n", user.name.c_str());
    printf("\033[4;12H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[5;12H｜                                                   ｜\n");
    printf("\033[6;12H｜                                                   ｜\n");
    printf("\033[7;12H｜                                                   ｜\n");
    printf("\033[8;12H｜                                                   ｜\n");
    printf("\033[9;12H｜                                                   ｜\n");
   printf("\033[10;12H｜                                                   ｜\n");
   printf("\033[11;12H｜                                                   ｜\n");
   printf("\033[12;12H｜                                                   ｜\n");
   printf("\033[13;12H｜                                                   ｜\n");
   printf("\033[14;12H｜                                                   ｜\n");
   printf("\033[15;12H｜                                                   ｜\n");
   printf("\033[16;12H｜___________________________________________________｜\n");
   printf("\033[17;12H＊                                                   ＊\n");
   printf("\033[18;12H｜                                                   ｜\n");
   printf("\033[19;12H＊___________________________________________________＊\n");
   printf("\033[20;12H｜                                                   ｜\n");
   printf("\033[21;12H｜   ＊1.群成员               ＊2.管理员                ｜\n");
   printf("\033[22;12H｜   ＊3.进入群聊             ＊4.退群                  ｜\n");
   printf("\033[23;12H｜   ＊5.处理申请             ＊6.踢人                  ｜\n");
   printf("\033[24;12H｜   ＊7.传输文件             ＊8.接受文件               ｜\n");
   printf("\033[25;12H｜   ＊9.退出                                         ｜\n");
   printf("\033[26;12H＊___________________________________________________＊\n\n");

    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      check_member(user);
      break;
    case 2:
      set_manager(user);
      break;
    case 3:
      chat_group(user);
      break;
    case 4:
      withdraw_group(user);
      break;
    case 5:
      deal_group_req(user);
      break;
    case 6:
      kick_sb(user);
      break;
    case 7:
      send_file_gro(user);
      break;
    case 8:
      recv_file_gro(user);
    }
    if (select == 9)
    {
      break;
    }
  }
  system("clear");
}

void disband_group(jjjson::usr user)
{
  char *f;
  cout << "请输入解散的群聊" << endl;
  cin >> user.group;
  user.choice = "look_g";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] == '1')
  {
    cout << "该群不存在" << endl;
    free(f);
    return;
  }
  else if (f[0] != '6')
  {
    cout << "你不是该群群主" << endl;
    free(f);
    return;
  }
  free(f);
  cout << "*****1.确认     2.取消*****" << endl;
  string a;
  cin >> a;
  if (a != "1")
    return;
  else
  {
    user.choice = "disband_group";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
  }
}

void Group(jjjson::usr user)
{
  while (1)
  {
    // Inform(user);
    char *buf;
    string s;
    json j;
    user.choice = "look_group";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
    recvMsg(cfd, &buf);
    
    buf[strlen(buf)] = '\0';
    string t(buf);
    free(buf);
    j = json::parse(t);
    auto tmp = j.get<jjjson::myGroup>();
    cout << "*********群名       ********身份********" << endl;
    for (auto it = tmp.mygroup.begin(); it != tmp.mygroup.end(); it++)
    {
      cout << "        " << *it << "              ";
      if (tmp.status[*it] == 1)
      {
        cout << "owner" << endl;
      }
      else if (tmp.status[*it] == 2)
      {
        cout << "manager" << endl;
      }
      else if (tmp.status[*it] == 3)
      {
        cout << "member" << endl;
      }
    }
    printf("\033[2;12H ____________________________________________________\n");
    printf("\033[3;12H｜              (^_^)    welcome %s                  ｜\n", user.name.c_str());
    printf("\033[4;12H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[5;12H｜                                                   ｜\n");
    printf("\033[6;12H｜                                                   ｜\n");
    printf("\033[7;12H｜                                                   ｜\n");
    printf("\033[8;12H｜                                                   ｜\n");
    printf("\033[9;12H｜                                                   ｜\n");
   printf("\033[10;12H｜                                                   ｜\n");
   printf("\033[11;12H｜                                                   ｜\n");
   printf("\033[12;12H｜                                                   ｜\n");
   printf("\033[13;12H｜                                                   ｜\n");
   printf("\033[14;12H｜                                                   ｜\n");
   printf("\033[15;12H｜                                                   ｜\n");
   printf("\033[16;12H｜___________________________________________________｜\n");
   printf("\033[17;12H＊                                                   ＊\n");
   printf("\033[18;12H｜                                                   ｜\n");
   printf("\033[19;12H＊___________________________________________________＊\n");
   printf("\033[20;12H｜                                                   ｜\n");
   printf("\033[21;12H｜   ＊1.建群                ＊2.加群                  ｜\n");
   printf("\033[22;12H｜   ＊3.进群                ＊4.解散群                ｜\n");
   printf("\033[23;12H｜   ＊5.退出                                         ｜\n");
   printf("\033[24;12H｜                                                   ｜\n");
   printf("\033[25;12H｜                                                   ｜\n");
   printf("\033[26;12H＊___________________________________________________＊\n\n");

    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      Build_group(user);
      break;
    case 2:
      Join_group(user);
      break;
    case 3:
      Enter_group(user);
      break;
    case 4:
      disband_group(user);
      break;
    }
    if (select == 5)
    {
      break;
    }
  }
  system("clear");
}

int Logout(jjjson::usr user)
{
  char *f;
  user.choice = "logout";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] == '1')
  {
    free(f);
    return 1;
  }
  else
  {
    free(f);
    return 0;
  }
}

