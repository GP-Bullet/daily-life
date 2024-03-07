//*1纯虚函数 和 抽象类
//因为父类中的虚函数 没什么用
// virtual 返回值类型 函数名 （） =0
//抽象类 无法实例化对象
//子类必须重写父类中的纯虚函数，否则也无法实例化

//抽象类  煮咖啡 煮茶叶


//*2  一个类 究竟是一个 个体 还是 一个动作（一个过程）



//*3 虚析构和纯虚析构
//delete父类时并不会走子类的析构代码造成内存泄露
//vitual ~Animal()
//解决 父类指针 释放 子类对象时 不干净的问题


//纯虚析构 也需要具体的实现 为了解决父类也有开辟到堆区
//也属于抽象类


#include<iostream>

using namespace std;

class CPU
{
public:
    virtual void calculate()=0;
};

class View
{
public:
    virtual void xianshi()=0;
};
class Memory
{   
public:
    virtual void cunchu()=0;
};
class Computer
{
public:
    Computer(CPU*cpu,View*vc,Memory*mem)
    {
        m_cpu=cpu;
        m_view=vc;
        m_mem=mem;
    }
    void work()
    {
        m_cpu->calculate();
        m_view->xianshi();
        m_mem->cunchu();
    }
    ~Computer()
    {
        if(m_cpu!=NULL)delete m_cpu;
        
    }

private:
    CPU *m_cpu;
    View  *m_view;
    Memory *m_mem;
};

class IntelCPU:public CPU
{
public:
    virtual void calculate(){
        cout<<"intel CPU"<<endl;
    }
};
class IntelView:public View
{
public:
    virtual void xainshi(){
        cout<<"intel xianshi"<<endl;
    }
};
class Intelneicun:public Memory
{
public:
    virtual void cunchu(){
        cout<<"intel cunchu"<<endl;
    }
};

class  lenveoCPU:public CPU
{
public:
    virtual void calculate(){
        cout<<"lenveo CPU"<<endl;
    }
};
class lenveoView:public View
{
public:
    virtual void xainshi(){
        cout<<"lenevo xianshi"<<endl;
    }
};
class lenveoneicun:public Memory
{
public:
    virtual void cunchu(){
        cout<<"lenveo cunchu"<<endl;
    }
};

void test01()
{
    CPU*IntelCpu=new IntelCPU;
    View* intelcard=new IntelView;
    Memory* intelmem=new Intelneicun;
}