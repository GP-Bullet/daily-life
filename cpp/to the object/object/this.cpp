#include<iostream>
#include<string>
using namespace std;



/*
成员变量和成员函数分开存储
!只有非静态成员 属于类的对象上

this指针 

*/

class Person{
    int m_A;//
};
void test01(){

}
int main(){
    Person a;

    //!空对象占用一个字节   C++编译器为了区分空对象占内存的位置


    return 0;
}