#include<iostream>
using namespace std;

/*
空指针调用成员函数  可以访问函数
m_age 默认会有 this->age  当前对象的指针  空的值无法访问属性
*/

/
class Person
{

public:
    void showClassName()
    {

    }
};

