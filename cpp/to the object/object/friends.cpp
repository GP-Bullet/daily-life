//友元

#include<string>
#include<iostream>
using namespace std;


//全局函数  
class Building
{   //1.全局函数作为友元 放到类里面即可
    //2。友元类友元函数 
    //3.成员函数做友元
    friend class Goodman;
    friend void goodman(Building* building);
    friend void Goodman::visit();

public:
    string m_setroom;
private:
    string m_bedroom;
};

Building::Building()
{
    m_setroom="客厅";
    m_bedroom="woshi";
};
Goodman::Goodman(){
    Building=new Building;
};


class Goodman
{
public:
    Goodman();
    void visit(); //参观函数 访问Building中的属性
    Building *buliding;
};
