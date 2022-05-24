/*
出厂设置和清理数据
构造函数和析构函数
*/

//构造函数没有返回值，函数名和类名相同，可以有参数  自动调用只会调用一次
//~析构函数  不可以有参数



#include<string>
#include<stdlib.h>
#include<iostream>
using namespace std;
class Person
{
public:
    //构造
    Person ()
    {
        cout<<"sdffasd"<<endl;
    }
    //析构
    ~Person()
    {
        cout<<"lallaalal"<<endl;
    }
};
int main(){

    Person p1;

    getchar();
    return 0;
}