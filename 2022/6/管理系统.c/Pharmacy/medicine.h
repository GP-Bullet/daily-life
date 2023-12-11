#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>  //用于*输入密码





struct medicine   //药结构体 
{
    char num[10];
    char name[100];
    double price;
    int cnt;
    double total;
    struct medicine * next;
} med;

struct user //人结构体 
{
    struct user*next;
    char  zh[30];
    char mm[30];
    
};

void init_medicine();
void show_notice();
void show_all();
int password(char *zh);
void check_good();
void message();
void purchase();
void show_message();
void add();
void dlete_medicine();
void dlete_user();
void modify();
void check_income();
void notice();
void menu_consumer();
void menu_manager();
void mod_pwd();
void get_pwd(char *buf);
void login_user();
void init_user();
void sign_up_user();
void destory_user();
void destory_medicine();
void insert_medicine();
void logout();
void down_sort(struct medicine * L,int flag);
void up_sort(struct medicine * L,int flag);
void dlete_manager();
void add_manager();
void logout();
