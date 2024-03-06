/*
访问权限
公共     成员   类内可以访问 类外也可以访问
保护           类内可以访问 类外不可以访问       继承   父亲中的保护权限儿子可以访问
私有           类内可以访问 类外不可以访问              


*struct 和 class 区别 
默认权限为公有
class默认为私有

成员属性设置为私有
1。自己可以控制读写的权限
2.检测数剧的有效性
*/


#include<iostream>
using namespace std;

class Person
{
public:
    string m_Name;
protected:
    string m_Car;
private:
    int m_Password;
public:
    void func()
    {
        m_Name="qwe";
        m_Car="lalal";
        m_Password=123;
        cout<<m_Name<<" "<<m_Car<<endl;
    }
};

int main(){
    Person p1;
    p1.func();
    cout<<p1.m_Name<<" ";
   // cout<<p1.m_Car<<endl;

}