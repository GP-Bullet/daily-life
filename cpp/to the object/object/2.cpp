#include<iostream>
#include<string>
using namespace std;

class student
{
public:
    //属性
    string m_name;
    int m_id;
    //行为
    void printStu(){
        cout<<"姓名:"<<m_name<<" "<<"学号： "<<m_id<<endl;
    }
        //给姓名赋值
    void setName(string name){
        m_name=name;
    }
    void setId(int num){
        m_id=num;
    }
};

int main(){
    student stu1;
    stu1.setName("小明");
    stu1.setId(123);

    
    stu1.printStu();
    return 0;
}