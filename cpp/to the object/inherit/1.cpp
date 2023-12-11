//公共的头部底部  用继承
//太多重复代码
//减少代码量
//语法：class 子类名（派生类）：继承方式 父类名（基类）
#include<iostream>


using namespace std;

//继承实现页面

//公共页面
class Base
{
public:
    void header()
    {
        cout<<"导航栏"<<endl;
    };
    void footer()
    {
        cout<<"底部版权"<<endl;
    };
    void left()
    {
        cout<<"JAVA,C++,Python"<<endl;
    };
};

class Java: public Base
{
public:
    void content()
    {
        cout<<"JAVA video"<<endl;
    };
};
class CPP: public Base
{
public:
    void content()
    {
        cout<<"CPP video"<<endl;
    };
};
class Python: public Base
{
public:
    void content()
    {
        cout<<"Python video"<<endl;
    };
};

void test01(){
    //Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	//Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	//C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();
}
int main(){
    test01();

    return 0;
}