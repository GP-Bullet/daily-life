//多态  静态多态 动态多态

//父子类型可转换

//地址早绑定 晚绑定
#include<iostream>

using namespace std;
//虚函数
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
