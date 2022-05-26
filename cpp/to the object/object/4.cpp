#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
    //设置
    void setName(string name){
        m_Name=name;
    }
    //获取
    string showName(){
        return m_Name;
    }
    int getAge(){

        return m_Age;
    }
    void setAge(int age){
        if(age<0 ||age>150){
            m_Age=0;
            cout<<"wrong age"<<endl;
            return ;
        }
        m_Age=age;
        
    }
    void setLove(string lover){
        m_lover=lover;
    }

private:
    //可读可写
    string m_Name;
    //只读d
    int m_Age;
    //只写
    string m_lover;

};

int main(){
    Person p1;
    p1.setName("asdf");
    p1.setLove("loverrrr");
    p1.setAge(20);
    cout<<p1.showName()<<" "<<p1.getAge();
}