#include<iostream>
#include<string>
using namespace std;

/*
类中的成员可以是另一个类的对象，  对象成员

当其他类的对象作为本类成员，先构造类对象，再构造自身   构造函数
析构的顺序相反
*/
class Phone
{
    
public:
   // void GetName(string PName){
    //    m_PName=PName;
   // }
    //错了要用构造函数】
    string m_PName;
    Phone(string PName){
        m_PName=PName;
    }
};

class Person
{
    
public:
    //Phone m_Phone=PName
    Person(string name,string PName):m_Name(name),m_phone(PName){ //初始化列表

    }
    string m_Name;
    Phone m_phone;
};
void test01()
{
    Person p("dfsaf","huawei");   //此时把Phone也构造了   
    /*

    */

    cout <<p.m_Name<<"yong"<< " " << p.m_phone.m_PName<<endl;
}
int main(){
    test01();
    return 0;
}