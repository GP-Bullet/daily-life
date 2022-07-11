#include<iostream>
using namespace std;

//对权限的理解   权限的重要性
//类内 类外

//*继承方式
//?配合友元 


class A
{
public:
    int a;
protected:
    int b;
private:
    int c;
};
class B:protected A
{

protected:
    void func(){
        a=10;
        b=20;
    }
};

void myClass()
{
    B s1;
    s1.a;

}

int main(){
    return 0;
}