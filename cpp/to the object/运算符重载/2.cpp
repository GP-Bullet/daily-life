/*
左移运算符
重载
通常你不会利用函数重载<<运算符


Person p
p.m_A=10
p.m_B=10
cout << p << endl;

*/
#include<iostream>
using namespace std;

class Person
{
public:
    
    int m_A;
    int m_B;
};   
//利用友元的技术，可以访问私有内容 
ostream &operator<<(ostream &cout,Person &p)
{
    cout <<"m_A="<<p.m_A<<"m_B="<<p.m_B;
    return cout;
}

void test01()
{
    Person p;
    p.m_A=10;
    p.m_B=10;
    cout <<p<<endl;
    
}
int main(){
    test01();
    return 0;
}