//继承中的对象模型
//继承的属不属于对象中的
//父类中的所有非静态成员属性都被子类继承下去
//父类中的私有成员属性 是被编译器给隐藏了，因此是访问不到
//但是确实被继承下去了


//2继承中构造和析构顺序  
//父构子构
//子析父析

//!静态成员
#include<iostream>
using namespace std;
class Base
{
public:
    Base(){
        cout<<"Base gouzao"<<endl;
    }
    ~Base(){
        cout<<"Base xigou"<<endl;
    }
};
class B:public Base
{
public:
    B(){
        cout<<"B gouzao"<<endl;
    }
    ~B(){
        cout<<"B xigou"<<endl;
    }
};

void test01(){
    B b;
}
int main(){
    test01();
    return 0;
}