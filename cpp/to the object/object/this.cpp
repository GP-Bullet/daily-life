#include<iostream>
#include<string>
using namespace std;



/*
成员变量和成员函数分开存储
!只有非静态成员 属于类的对象上


this指针 
解决名称冲突
返回对象本身
隐含在每个成员函数内部
*/

class Person{
public:
    Person(int age){
        //this指针指向的是   被调用的成员函数   所属的对象  this->  p1->age
        this->age=age;
    }
    int age;
    Person& Personadd(Person &p1){//返回若用的是引用      返回若用值创建一个新的对象 
        this->age=p1.age;
        return *this;
        //链式编程
    }
};
void test01(){

}
void test02(){

}
int main(){
    Person p1(10);

    //!空对象占用一个字节   C++编译器为了区分空对象占内存的位置、

    return 0;
}