#pragma once
#include"allinclude.h"
#include"cli_group.cpp"
#include"cli_ui.cpp"
#include"cli_friend.cpp"

#define SIZE 200000
#define LOGSLEEP 150000
#define LOGSLEEP2 7000

int menu(jjjson::usr user)
{
  while (1)
  {
    // Check(user);
    // Inform(user);
    //     time_t timep;
    // time(&timep);
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
   printf("\033[21;12H｜   ＊1.个人信息             ＊2.好友                  ｜\n");
   printf("\033[22;12H｜   ＊3.群聊                 ＊4.点赞                  ｜\n");
   printf("\033[23;12H｜   ＊5.注销账号             ＊6.退出                  ｜\n");
   printf("\033[24;12H｜                                                   ｜\n");
   printf("\033[25;12H｜                                                   ｜\n");
   printf("\033[26;12H＊___________________________________________________＊\n\n");
  //  printf("\033[3;23HTIME: %s\n",asctime(gmtime(&timep)));
  //   printf("  ***********           4.查看通知               ***********  \n");
  //   printf(" ***********            5.注销账号                **********  \n");
  //   printf(" ***********            6.退出                      **********  \n");
    string select;
    cin >> select;
    if (select == "1")
    {
      settings(user);
    }

    else if (select == "2")
    {
      Friend(user);
    }
    else if (select == "3")
    {
      Group(user);
    }
    else if(select=="4")
    {

    }
    else if (select == "5")
    {
      if (Logout(user))
      {
        cout << "注销成功" << endl;
        return 0;
      }
      else
        cout << "注销失败" << endl;
    }

    else if (select == "6")
    {
       user.choice = "offline";
       json j;
       j = user;
       string ifo = j.dump();
       char *buf;
       sendMsg(cfd, ifo, ifo.size());

       recvMsg(cfd, &buf);
       if (strcmp(buf, "1") == 0)
       {
       cout << "|                    退出成功                |\n";
        sleep(1);
       }
       free(buf);
       // system("clear");
      break;
    }
    else
    {
      cout << "请输入正确选项！" << endl;
    }
  }
  return 0;
}
void login()
{
  jjjson::usr user;

  // user.id=(int)time(NULL);
  // printf("注册ID为%d\n请注意保存",user.id);
  user.choice = "login";
  printf("|              请输入用户名              |\n");
  cin >> user.name;

  user.pwd = getpass("|              请输入密码                   |\n");
  json j;
  j = user;
  string ifo = j.dump();
  char buf[1];
  user.answer = "";
  user.box.clear();
  user.fd = 0;
  user.friendid = 0;
  user.friendname = "";
  user.id = 0;
  user.mes_fri = "";
  user.question = "";
  user.time = 0;
  user.status = 0;
  sendMsg(cfd, ifo.c_str(), ifo.size());
  read(cfd, buf, 1);
  if (strcmp(buf, "1") == 0)
  {
    cout << "login sucuess!" << endl;
    pthread_t t;
     pthread_create(&t, NULL, Inform, (void *)&user);
    menu(user);
  }
  else if (strcmp(buf, "2") == 0)
  {
    cout << "password error " << endl;
  }
  // else if(strcmp(buf, "6") == 0)
  //{
  // cout<<"此账号已经登录！"<<endl;
  //}
  else
  {
    cout << "don't exit the account" << endl;
  }
}

void loading1_dis()
{
    system("clear");
    printf("\033[12;50H＊\n");
    usleep(SIZE);
    printf("\033[12;52H用\n");
    usleep(SIZE);
    printf("\033[12;54H心\n");
    usleep(SIZE);
    printf("\033[12;56H去\n");
    usleep(SIZE);
    printf("\033[12;58H做\n");
    usleep(SIZE);
    printf("\033[12;60H! \n");
    usleep(SIZE);
    printf("\033[12;50H  \n");
    usleep(SIZE);
    printf("\033[12;52H  \n");
    usleep(SIZE);
    printf("\033[12;54H  \n");
    usleep(SIZE);
    printf("\033[12;56H  \n");
    usleep(SIZE);
    printf("\033[12;58H  \n");
    usleep(SIZE);
    printf("\033[12;60H  \n");
    usleep(SIZE);
    printf("\033[14;62H代\n");
    usleep(SIZE);
    printf("\033[14;64H码\n");
    usleep(SIZE);
    printf("\033[14;66H因\n");
    usleep(SIZE);
    printf("\033[14;68H你\n");
    usleep(SIZE);
    printf("\033[14;70H而\n");
    usleep(SIZE);
    printf("\033[14;72H精\n");
    usleep(SIZE);
    printf("\033[14;74H彩\n");
    usleep(SIZE);
    printf("\033[14;76H＊\n");
    usleep(SIZE);
    printf("\033[14;62H  \n");
    usleep(SIZE);
    printf("\033[14;64H  \n");
    usleep(SIZE);
    printf("\033[14;66H  \n");
    usleep(SIZE);
    printf("\033[14;68H  \n");
    usleep(SIZE);
    printf("\033[14;70H  \n");
    usleep(SIZE);
    printf("\033[14;72H  \n");
    usleep(SIZE);
    printf("\033[14;74H  \n");
    usleep(SIZE);
    printf("\033[14;76H  \n");
    usleep(SIZE);
    printf("\033[12;50H＊用心去做!\n");
    printf("\033[14;62H代码因你而精彩＊\n");
    printf("\033[16;50H____________________________\n");
    printf("\033[17;49H｜＊                        ｜\n");
    printf("\033[18;50H^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("\033[19;50H GP_ONLINE  Linux网络聊天室\n");
    printf("\033[20;65HLoading...%%8 \n");
    sleep(1);
    printf("\033[17;53H＊＊＊\n");
    printf("\033[20;76H37\n");
    sleep(1);
    printf("\033[17;59H＊＊＊＊＊＊\n");
    printf("\033[20;76H80\n");
    sleep(1);
    printf("\033[17;71H＊＊＊\n");
    printf("\033[20;76H100\n");
    sleep(1);
}
/* 登录界面 */
void log1_dis()
{
    system("clear");
    printf("\033[6;42H __\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________________________\n");
    usleep(LOGSLEEP);
    printf("\033[7;42H  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \n");
    usleep(LOGSLEEP);
    printf("\033[7;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[8;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[10;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[11;42H＊__\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________________________＊\n");
    usleep(LOGSLEEP);
    printf("\033[12;42H  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
    usleep(LOGSLEEP);
    printf("\033[12;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[19;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[21;42H＊————————————————————————————————————————————————＊\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜   ________                                     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜______｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜(^**^)｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜   ________       ___________________________   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜  ｜      ｜     ｜                         ｜  ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜(^**^)｜      ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜______｜      ___________________________   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;42H｜                 ｜                         ｜  ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;42H｜                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;42H｜               GP_ONLINE  聊天室                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;57H用户名\n");
    usleep(LOGSLEEP);
    printf("\033[17;57H密码\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊1.登录                                     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊1.登录                         ＊4.退出 ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊1.登录 ＊2.注册             ＊4.退出 ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊1.登录 ＊2.注册 ＊3.忘密 ＊4.退出 ｜\n");
}
int login1_menu()
{
  while (1)
  {
    int select;
    system("clear");
    printf("\033[6;42H __________________________________________________\n");
    printf("\033[7;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[8;42H｜                                                ｜\n");
    printf("\033[9;42H｜               GP_ONLINE  聊天室                 ｜\n");
    printf("\033[10;42H｜                                               ｜\n");
    printf("\033[11;42H＊________________________________________________＊\n");
    printf("\033[12;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[13;42H｜   ________       ___________________________   ｜\n");
    printf("\033[14;42H｜  ｜      ｜ 用户名｜                         ｜  ｜\n");
    printf("\033[15;42H｜  ｜(^**^)｜      ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    printf("\033[16;42H｜  ｜______｜      ___________________________   ｜\n");
    printf("\033[17;42H｜             密码｜                         |    ｜\n");
    printf("\033[18;42H｜                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    printf("\033[19;42H｜                                                ｜\n");
    printf("\033[20;42H｜＊1.登录     ＊2.注册      ＊3.忘密       ＊4.退出  ｜\n");
    printf("\033[21;42H＊————————————————————————————————————————————————＊\n");
    fflush(stdin);
    printf("\033[28;71H                                      \n");
	  printf("\033[28;45H＊Please input your choice:");
    scanf("%d", &select);
    switch (select)
    {
    case 1:
      login();
      break;
    case 2:
      sign_up();
      break;
    case 3:
      Find_pwd();
      break;
    case 4:
      break;
    }
    if (select == 4)
    {
      break;
    }
  }
  
    system("clear");
    return 1;
  
}