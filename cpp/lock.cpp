#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<cstring>
#include<stdlib.h>
using namespace std;

map<string,int>var;
int n=0,t1=0,t2=0,t3=0,t4=0,t5=0,q=0;

bool lock=false,enter=true,last=false;
struct pro{
    int id,now,sum;//编号，执行到哪，程序行数
    string action[30][2];
}num,aa;
string temp,waste;
deque<pro>wait,stop;//双端队列


int main(){
    int t=0;
    cin>>t;
    while(t--){
        lock=false,enter=true,last=false
    }
}