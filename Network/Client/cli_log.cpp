#pragma once
#include"allinclude.h"
#include"cli_recv.cpp"

void *Inform(void *arg)
{
  pthread_detach(pthread_self());
  json j;
  int ret = 0;
  struct sockaddr_in ser;

  int ccfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&ser, sizeof(ser));
  ser.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &ser.sin_addr);
  ser.sin_port = htons(PORT);
  // // pthread_create(&tid,NULL,Recv,void *base)
  connect(ccfd, (struct sockaddr *)&ser, sizeof(ser));

  jjjson::usr u = *(jjjson::usr *)arg;
  u.fd = ccfd;
  u.choice = "inform";
  j = u;
  string s = j.dump();
  json k;
  string p;
  sendMsg(u.fd, s, s.size());
  while (1)
  {
    char *buf;
  ret = recvMsg(u.fd, &buf);
      ;
    // cout<<"lll:::"<<buf<<endl;

    cout << ret << endl;
    if (strcmp(buf, "exit") == 0)
    {
      cout << "您离线了" << endl;
      free(buf);
      close(ccfd);
      return NULL;
    }
    // k = json::parse(buf);
    // auto q = k.get<jjjson::mymessage>();
    // for (auto it = q.mes.begin(); it != q.mes.end(); it++)
    //{
    // if (*it == "exit")
    //{
    //   cout << "you are quit" << endl;
    //  close(ccfd);
    //  return NULL;
    //}
    // cout << "*****inform::" << *it<< endl;
    //}

    //cout << "|                    通知                          |" << buf << endl;
    free(buf);
  }
}
void Check(jjjson::usr user)
{
  char *f;
  user.choice = "check";
  json j = user;
  string s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (strcmp(f, "1") == 0)
  {
    cout << "有通知请注意查收！" << endl;
  }
  free(f);
}

void sign_up()
{
  jjjson::usr user;

  // user.id=(int)time(NULL);
  // printf("注册ID为%d\n请注意保存",user.id);
  user.choice = "sign";
  printf("请输入用户名！\n");
  cin >> user.name;
  user.pwd = getpass("请输入密码!\n");
  printf("请设置密保问题！\n");
  cin >> user.question;
  printf("请设置密保答案！\n");
  cin >> user.answer;
  user.status = 0;
  user.id = 0;
  user.time = 0;
  user.buf.clear();
  user.friendid = 0;
  json j;
  j = user;
  string ifo = j.dump();
  char buf[1];
  memset(buf, 0, 1);
  sendMsg(cfd, ifo, ifo.size());
  read(cfd, buf, 1);
  if (strcmp(buf, "1") == 0)
  {
    cout << "|             注册成功              |" << endl;
    sleep(1);
  }
  else
  {
    cout << "|          该用户已经注册!          |" << endl;
    sleep(1);
  }
  return;
}

void settings(jjjson::usr user)
{
  while (1)
  {
    // Inform(user);
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
   printf("\033[21;12H｜   ＊1.昵称             ＊2.密码                     ｜\n");
   printf("\033[22;12H｜                                                   ｜\n");
   printf("\033[23;12H｜   ＊3.密保问题          ＊4.答案                     ｜\n");
   printf("\033[24;12H｜                                                   ｜\n");
   printf("\033[25;12H｜   ＊5.退出                                         ｜\n");
   printf("\033[26;12H＊___________________________________________________＊\n\n");
   printf("\033[3;23HTIME: %s\n",asctime(gmtime(&timep)));

    int select;
    cin >> select;
    switch (select)
    {
    case 1:
      cout << "请输入新昵称" << endl;
      cin >> user.name;
      break;
    case 2:
      cout << "请输入新密码" << endl;
      cin >> user.pwd;
      break;
    case 3:
      cout << "请输入新密保" << endl;
      cin >> user.question;
      break;
    case 4:
      cout << "请输入新答案" << endl;
      cin >> user.answer;
      break;
    }
    if (select == 5)
    {
      user.choice = "settings";
      json j;
      j = user;
      string ifo = j.dump();
      char buf[1];
      memset(buf, 0, 1);
      sendMsg(cfd, ifo, ifo.size());
      read(cfd, buf, 1);
      if (strcmp(buf, "1") == 0)
      {
        cout << "修改成功！" << endl;
        sleep(1);
      }
      // else
      // {
      //   cout << "修改失败！" << endl;
      //   sleep(1);
      // }
      break;
    }
  }
}

void Find_pwd()
{
  json j;
  string s;
  char *f;
  cout << "请输入要找回密码的账号" << endl;
  jjjson::usr user;
  cin >> user.friendname; //其实是偷懒为了方便，因为服务器只写了个看好友的
  user.name = user.friendname;
  user.choice = "check_friend";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &f);
  if (f[0] == '0')
  {
    cout << "账号不存在" << endl;
    free(f);
    return;
  }
  free(f);
  char *buf;
  user.choice = "find_pwd";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  recvMsg(cfd, &buf);

  j = json::parse(buf);
  free(buf);
  auto tmp = j.get<jjjson::usr>();
  cout << "密保问题是:" << tmp.question << endl;
  cout << "请输入密保答案" << endl;
  cin >> user.answer;
  user.choice = "true_pwd";
  j = user;
  s = j.dump();
  sendMsg(cfd, s, s.size());
  char *bu;
  recvMsg(cfd, &bu);
  j = json::parse(bu);
  free(bu);
  tmp = j.get<jjjson::usr>();
  if (tmp.pwd != "")
  {
    cout << "请记住密码 ：" << tmp.pwd << endl;
    sleep(1);
  }
  else
  {
    cout << "密保答案错误！" << endl;
    sleep(1);
  }
}