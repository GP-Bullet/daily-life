#include<iostream>
#include<string>
//调用规则
/*
写了有参构造编译器不在提供默认构造 还会调用拷贝构造
如果我们写了拷贝构造函数，编译器不在提供其他的构造函数

深拷贝与浅拷贝
浅拷贝：简单的赋值拷贝操作  new 堆区的内存重复释放
深拷贝：自己写拷贝函数，m_Height=new int (*p.m_Height);

if(m_Height != NULL){
    delete m_Height
    m_Height =NULL;
}
*/

//初始化列表  构造函数

class Person
{
public:
    Person(int a);
    int m_A;
    int m_B;
    int m_C;
    Person(int age,int height)
    {
    }

    Person(int a,int c,int c):m_A(a),m_B(b),m_C(c){
    }
};
