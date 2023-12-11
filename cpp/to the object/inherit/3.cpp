//*1继承中的对象模型
//继承的属不属于对象中的
//父类中的所有非静态成员属性都被子类继承下去
//父类中的私有成员属性 是被编译器给隐藏了，因此是访问不到
//但是确实被继承下去了


//*2继承中构造和析构顺序  
//父构子构
//子析父析

//*3继承同名成员处理方式
//如果通过子类对象 访问到父类中的同名成员，需要加作用域

//直接调用，调用的是子类中的同名成员

//*继承+重载  
//如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉分类中所有同名成员函数
//若无则不用加作用域，否则要加

//*4继承中同名静态成员处理方法  
//静态成员和非静态成员出现同名，处理方式一致

//*5多继承语法
//class 子类：继承方式 父类1, 继承方式 父类2
//不太建议使用
//同名加作用域


//!静态成员   静态成员有多重要？
//静态成员变量 所有对象都共享同一份数据 编译阶段就分配内存
//类内声明 类外初始化
//静态成员函数 只能访问静态的成员变量
//静态访问： 通过对象来访问数据 
//          通过类名来访问数据


#include<iostream>
using namespace std;
class Base
{
public:
    Base(){
        cout<<"Base gouzao"<<endl;
        //static int m_A=100; 

    }
    static int m_A;
    ~Base(){
        cout<<"Base xigou"<<endl;
    }
    static void func(){
        cout<<"Base func"<<endl;
    } 

};
int Base::m_A=100;

class B:public Base
{
public:
    B(){
        cout<<"B gouzao"<<endl;
        m_A=200;
    }
    static int m_A;
    ~B(){
        cout<<"B xigou"<<endl;
    }
    static void func(){
        cout<<"B func"<<endl;
    } 
};
int B::m_A=200;

void test01(){
    B b;
    cout<<b.m_A<<endl;
    cout<<b.Base::m_A<<endl;

    cout<<B::m_A<<endl;
    cout<<Base::m_A<<endl;
    cout<<B::Base::m_A<<endl;
    //第一个冒号代表通过类名方式访问 第二个冒号代表访问父类作用域下
}
void test02(){
    B s;
    s.func();
    s.Base::func();

//通过类名
    B::func();
    Base::func();
}
int main(){
    test02();
    return 0;
}