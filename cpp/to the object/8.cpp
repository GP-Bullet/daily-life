#include<string>
#include<stdlib.h>
#include<iostream>
using namespace std;

/*
构造分类：  有参无参        普通构造 拷贝构造


调用方式： 括号法   显示法   隐式转换法
!调用无参构造 不能用（）  因为编译器会认为是一个函数的声明


显示法
!1、*匿名对象   特点：当前行执行结束后，系统会立即回收掉匿名对象
!2、不要利用拷贝构造函数 初始化匿名对象   Person(p3);   ==Person p3;

*/
class Person
{
    
public: 
    int age;
    Person(){
        cout<<"Person的无参构造"<<endl;
    }
    Person(int a){
        age=a;
        cout<<"Person的有参构造"<<endl;
    }
    //拷贝构造  
    Person (const Person &p)     //把所有属性拷贝到当前人    引用
    {
        age=p.age;
        cout<<"Person的copy构造"<<endl;
    }
    
    ~Person(){
        cout<<"Person的析构"<<endl;
    }

};


int main(){

    //括号法
    //Person p1; cout<<p2.age<<" "<<p3.age<<endl;
    //Person p2(10);
    //Person p3(p2);

    //显示法
    Person p1;
    Person p2=Person(10);    //有参
    Person p3=Person(p2); 

    Person(10); //匿名对象   特点：当前行执行结束后，系统会立即回收掉匿名对象

    //隐式转换法
    Person p4=10;  //Person p4=Person(10);
    Person p5=p4;


    return 0;
}