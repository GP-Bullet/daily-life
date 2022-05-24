/*
类
对象
属性  行为

封装 属性和行为作为一个整体
    加以权限控制
*/

#include<iostream>
using namespace std;

const double PI =3.14;

//圆类  2* PI * 半径

class Circle 
{   
    //权限
public:  
    //属性
    int m_r;
    //行为
    //获取圆的周长
    double cal_ZC(){
        return 2*PI*m_r;
    }
};


int main(){
    //通过圆类创建  具体的圆 --对象
    Circle c1;
    //属性赋值
    c1.m_r=10;
    cout<< "ZC="<<c1.cal_ZC()<<endl;


    return 0;
}

