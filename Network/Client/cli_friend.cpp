#include"allinclude.h"
#include"cli_recv.cpp"

void Add_friend(jjjson::usr user)
{
  cout <<"  "<< "\033[5;12H"<<"   请输入你想添加的好友用户名！" << endl;
  cin >> user.friendname;
  if (user.name == user.friendname)
  {
    cout << "请勿添加自己！" << endl;
    return;
  }
  user.choice = "add_friend";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  char *f;
  recvMsg(cfd, &f);
  if (strcmp(f, "0") == 0)
  {
    cout << "\033[7;12H"<< "此用户不存在！" << endl;
    sleep(1);
  }
  else if (strcmp(f, "2") == 0)
  {
    cout << "已经过发送请求！请勿重复发送！" << endl;
    sleep(1);
  }
  else if (f[0] == '3')
  {
    cout << "你们已经是好友" << endl;
    sleep(1);
  }
  else
  {
    cout <<"  "<< "\033[7;12H"<< "已成功发送！" << endl;
    sleep(1);
  }
  free(f);
}
void deal_req(jjjson::usr user)
{
  while (1)
  {

    char *buf;
    user.choice = "friend_req";
    json j = user;
    string s = j.dump();
    sendMsg(cfd, s, s.size());
    recvMsg(cfd, &buf);
    buf[strlen(buf)] = '\0';
    string tmp(buf);
    free(buf);
    j = json::parse(tmp);

    auto fri = j.get<jjjson::Friend>();
    for (auto it = fri.request.begin(); it != fri.request.end(); it++)
    {
      cout << "请求添加为好友" << *it << endl;
    }
    printf("     \033[6;12H         welcome %s         \n", user.name.c_str());
    printf("    \033[7;12H           1.处理           \n");
    printf("    \033[8;12H           2.退出              \n");
    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      cout << "请选择操作对象" << endl;
      string s;
      cin >> s;
      printf("    \033[6;12H  1.同意     2.拒绝      3.取消           \n");
      int x;
      cin >> x;
      if (x == 1)
        user.choice = "agree_friend";
      else if (x == 2)
        user.choice = "reject_friend";
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
void Delete_friend(jjjson::usr user)
{
  cout << "请输入想删除的用户（按0退出）" << endl;
  cin >> user.friendname;
  user.choice = "check_friend";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  char *f;
  recvMsg(cfd, &f);
  if (strcmp(f, "0") == 0)
  {
    cout << "此用户不存在！" << endl;
  }
  else if (strcmp(f, "3") != 0)
  {
    cout << "不是好友" << endl;
  }
  free(f);
  user.choice = "delete_friend";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  char *ff;
  recvMsg(cfd, &ff);
  // cout<<"this:: "<<ff<<endl;
  if (strcmp(ff, "1") == 0)
  {
    cout << "成功删除" << endl;
    sleep(1);
  }
  else
  {
    cout << "删除失败！" << endl;
    sleep(1);
  }
  free(ff);
}

void *recv_chat(jjjson::usr arg)
{ // pthread_detach(pthread_self());
  jjjson::usr tmp = arg;
  // tmp.choice = "recv_mes";
  json j = tmp;

  // string s = j.dump();
  //  send(cfd, s.c_str(), s.size(), 0);
  while (1)
  {

    char *buf;

    int ret = recvMsg(cfd, &buf);

    if ((strcmp(buf, "quit")) == 0)
    {
      free(buf);
      // cout << "gameover" << endl;
      break;
    }
    else
    {
      string t(buf);

      json j = json::parse(t);
      auto q = j.get<jjjson::Fri_chat>();
      for (auto it = q.unread.begin(); it != q.unread.end(); it++)
      {
        printf("%50c", ' ');
        cout <<  tmp.friendname << " :" << *it << endl;
        printf("%40c", ' ');
        cout << ctime(&q.unread_t[0]) << NONE << endl;
        q.unread_t.erase(q.unread_t.begin());
      }
    }
    free(buf);
  }
  return NULL;
}

void Check_history(jjjson::usr user)
{
  char *buf;
  user.choice = "check_history";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &buf);
  buf[strlen(buf)] = '\0';
  // cout<<"dfs"<<buf<<endl;
  string t(buf);
  free(buf);
  json k = json::parse(t);
  auto w = k.get<jjjson::Fri_chat>();
  for (auto it = w.history.begin(); it != w.history.end(); it++)
  {
    cout << *it << endl;
    cout << ctime(&w.time[0]) << endl;
    w.time.erase(w.time.begin());
    sleep(1);
  }
}

void send_file_fri(jjjson::usr user)
{
  while(1)
  {
  char path[1000], name[100];
  memset(path, 0, 1000);
  memset(name, 0, 100);
  int cnt = 0;
  cout << "请输入文件地址:(输入0退出)" << endl;
  cin >> path;
  if(strcmp(path,"0")==0)
  {
    break;
  }
  int sign;
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
  long long ret = 0;
  user.choice = "recv_file_fri";
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

void recv_file_fri(jjjson::usr user)
{
  while (1)
  {
    int fd;
    json j;
    string s;
    int flag = 0;
    user.choice = "check_file";
    char *buf;
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());
    recvMsg(cfd, &buf);
    string t(buf);
    free(buf);
    j = json::parse(t);
    auto x = j.get<jjjson::Fri_chat>();
    for (auto it = x.file.begin(); it != x.file.end(); it++)
    {
      cout << "*******" << *it << endl;
    }
    cout << "请选择操作对象(输入0退出)" << endl;
    string q;
    cin >> q;
    if (q == "0")
      break;
    for (auto it = x.file.begin(); it != x.file.end(); it++)
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

    user.choice = "send_file_fri";
    j = user;
    s = j.dump();
    sendMsg(cfd, s, s.size());

    long long ret = 0, ret2 = 0;
    char b[4096];
    memset(b, 0, 4096);
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

void Chat_sb(jjjson::usr user)
{
  char *f;
  printf(" ____________________________________________________\n");
  printf("｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
        cout << " |                     请输入聊天对象                   |" << endl;
  cin >> user.friendname;
  user.choice = "check_friend";
  json j = user;
  string r = j.dump();
  sendMsg(cfd, r, r.size());
  recvMsg(cfd, &f);
  
  //  cout<<"f=="<<f<<endl;
  if (f[0] == '0')
  {
    cout << "没有此人！" << endl;
    free(f);
    return;
  }
  else if (f[0] != '3')
  {
    cout << "不是好友" << endl;
    free(f);
    return;
  }
  if (f[0] == '3')
  {
    free(f);
    char *ff;
    user.choice = "check_shield";
    json c = user;
    string h = c.dump();
    sendMsg(cfd, h, h.size());
    recvMsg(cfd, &ff);
    if (ff[0] == '0')
    {
      cout << user.friendname << "已经屏蔽" << endl;
      free(ff);
      return;
    }
    free(ff);
  printf(" ____________________________________________________\n");
  printf("｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("开始和%s聊天，啦啦啦啦啦啦啦\n", user.friendname.c_str());
  }
          cout << "|             1.开始聊天                     |" << endl;
          cout << "|             2.查看聊天记录                  |" << endl;
          cout << "|             3.发文件                       |" << endl;
          cout << "|             4.收文件                       |"<< endl;
          cout << "|             5.退出                         |"<< endl;
  int select;
  cin >> select;
  if (select == 1)
  {
    json c;
    string h;
    pthread_t tid;
    thread recvv(recv_chat, user);
    user.choice = "offline_mes_fri";
    json k = user;
    string l = k.dump();
    sendMsg(cfd, l, l.size());
    user.choice = "chat_sb"; //唤醒
    user.mes_fri = "";
    c = user;
    h = c.dump();
    sendMsg(cfd, h, h.size());
    cout << "可以开始聊天辣";
    getchar();
    while (1)
    {
      string s;
      user.choice = "chat_sb";
      getline(cin,s);
      time_t t;
      t = time(NULL);
      user.mes_fri = s;
      
      user.time = t;
      if (s == "quit")
      {
        // user.choice = "quit_chatfri";
        json j = user;
        string l = j.dump();
        sendMsg(cfd, l, l.size());
        break;
      }
      cout  << user.name << " :" << s << endl;
      cout << ctime(&t) << NONE << endl;
      json j = user;
      string l = j.dump();
      sendMsg(cfd, l, l.size());
      
    }
    recvv.join();
  }
  else if (select == 2)
  {
    Check_history(user);
  }
  else if (select == 3)
  {
    send_file_fri(user);
  }
  else if (select == 4)
  {
    recv_file_fri(user);
  }
}

void Shield_fri(jjjson::usr user)
{

  char *f;
  printf(" ____________________________________________________\n");
  printf("｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
         cout << "|                       请输入对象                    |" << endl;
  cin >> user.friendname;
  user.choice = "check_friend";
  json j = user;
  string r = j.dump();
  sendMsg(cfd, r, r.size());
  recvMsg(cfd, &f);
  if (f[0] == '0')
  {
    printf("｜                     没有此人！                       ｜\n");
    free(f);
    return;
  }
  else if (f[0] != '3')
  {
    cout << "|         不是好友               |" << endl;
    free(f);
    return;
  }
  free(f);
  string s;
    printf(" ____________________________________________________\n");
    printf("｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("｜         1.屏蔽                                     ｜\n");
    printf("｜                   2.取消屏蔽                        ｜\n");
    printf("｜                                  3.退出            ｜\n");
   printf(" ｜___________________________________________________｜\n");
  cin >> s;
  if (s == "3")
    return;
  else
  {

    if (s == "1")
    {
      user.choice = "start_shield";
    }
    else if (s == "2")
    {
      user.choice = "canel_shield";
    }
    json j = user;
    string s = j.dump();
    sendMsg(cfd, s, s.size());
  }
}

void Friend(jjjson::usr user)
{
  while (1)
  {
    //system("clear");
    //Inform(user);
    
    time_t timep;
    time(&timep);
    system("clear");
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
   printf("\033[21;12H｜   ＊1.添加好友             ＊2.删除好友              ｜\n");
   printf("\033[22;12H｜                                                   ｜\n");
   printf("\033[23;12H｜   ＊3.私聊                ＊4.屏蔽好友               ｜\n");
   printf("\033[24;12H｜                                                   ｜\n");
   printf("\033[25;12H｜   ＊5.处理申请             ＊6.退出                 ｜\n");
   printf("\033[26;12H＊___________________________________________________＊\n\n");
   //printf("\033[3;23HTIME: %s\n",asctime(gmtime(&timep)));
    printf(" ____________________________________________________\n");
    printf("｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    cout <<"\n"<<"  |                        我的好友                      | " << endl;
    user.choice = "look_friend";
    json j = user;
    string s = j.dump();

    sendMsg(cfd, s, s.size());
    char *tmpfri;
    s.clear();
    recvMsg(cfd, &tmpfri);
    // tmpfri[strlen(tmpfri)] = '\0';
    // cout << "thiuss" << tmpfri << endl;
    s = tmpfri;
    free(tmpfri);
    // printf("111\n");
    // cout << "this" << s << endl;
    //````````````````````````````````````````````````````
    auto m = json::parse(s);

    auto fri = m.get<jjjson::Friend>();
    for (auto iter = fri.myfri.begin(); iter != fri.myfri.end(); iter++)
    {
      //````````````````````````````````````````````````
      char *f;
      memset(f, 0, 1);
      recvMsg(cfd, &f);
      cout << "|          " << *iter << "        ";
      if (f[0] == '0')
      {
        cout << "离线                  |" << endl;
      }
      else
      {
        cout << "在线                   |" << endl;
      }
      free(f);
    }
    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      Add_friend(user);
      break;
    case 2:
      Delete_friend(user);
      break;
    case 3:
      Chat_sb(user);
      break;
    case 4:
      Shield_fri(user);
      break;
    case 5:
      deal_req(user);
      break;
      // case 6 :
      // send_file(user);
      // break;
    }
    if (select == 8)
    {
      system("clear");
      return;
    }
    
  }
}