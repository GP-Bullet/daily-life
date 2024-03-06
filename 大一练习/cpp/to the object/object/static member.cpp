#include<string>
#include<iostream>

/*
静态成员变量

通过对象访问  通过类名访问

也是有访问权限的
*/

/*
静态成员函数
共用一个函数
*静态成员函数只能访问静态成员变量   通过
*/
class Person
{
public:
    
    //所有对象共享一份数据
    //编译阶段就分配内存
    //类内声明 类外初始化操作
    static int m_A;
    static void func()
    {   
        m_A=200;
        m_B=100;
        std::cout<<"hnahsu1"<<std::endl;
    }
    int m_B;
};
    int Person::m_A=100;
int main(){
    //通过类名访问
    std::cout<<Person::m_A<<std::endl;
    return 0;
}