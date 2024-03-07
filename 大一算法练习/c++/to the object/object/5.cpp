#include<iostream>
#include<string>
using namespace std;



//判断两个立方体是否相等

class Lifang
{
public:

    //获取表面积
    
    //获取体积
    //设置长宽高
    void setShuxing(int a,int b,int c){
        m_chang=a;
        m_kuan=b;
        m_gao=c;
    }   
    int getShuxing1(){
        return m_chang;
    }
    int getShuxing3(){
        return m_gao;
    }
        int getShuxing2(){
        return m_kuan;
    }


//利用成员函数判断两个立方体是否相等
    bool isSame(Lifang &c){     //引用方式传递
        if(m_L==c.getShuxing1())
    }
private:
    int m_chang;
    int m_kuan;
    int m_gao;
}；


int  main(){

}