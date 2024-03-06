//菱形继承
//利用虚继承 解决  在继承方式前加virtual
//动物（虚基类） 、 羊  驼 、 羊驼
//这个数据只有一份  
//底层  vbptr 虚基类指针 指向vbtable 虚基类表
//通过偏移量来找唯一一份数据

#include<iostream>
using namespace std;

class Animal 
{
public:  
    int age;
};
class sheep:virtual public Animal
{

};
class tuo:public Animal
{

};
class yangtuo:public sheep,public tuo
{

};
void test01()
{   

    yangtuo yt;
    yt.sheep::age=18;
    //菱形继承导致数据有两份，资源浪费
}
int main(){

}