//多态  静态多态 动态多态

//父子类型可转换

//地址早绑定 晚绑定
//虚函数
#include<iostream>

//动态多态满足条件 
//1、有继承关系
//2、子类重写父类的虚函数

//动态多态的使用
//父类的指针或者引用 指向子类对象
//Animal &animal =cat



//*原理
//指针
using namespace std;

class Animal
{
public:
    virtual void speak(){
        cout<<"动物在说话"<<endl;
    }
};

class Cat:public Animal
{
    void speak(){
        cout<<"小猫在说话"<<endl;
    }
};

class Dog:public Animal
{
    void speak(){
        cout<<"小狗在说话"<<endl;
    }
};


void dospeak(Animal &animal){
    animal.speak();
}

void test01(){
    Cat cat;
    Dog dog;
    dospeak(cat);
    dospeak(dog);
}


int main(){

    test01();
    return 0;
}

//?多态会不会使类弄的太多  代码风格

//!创建对象 和 new一个类 有什么区别 也相当于创建对象吗
//（开辟区域不同）  什么东西既能栈又能堆

//对类的理解 还能怎么深：知道是结构体 然后有不同的权限 
//它内部还有哪些指针 
//为什么叫实例化

