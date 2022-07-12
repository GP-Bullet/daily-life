#include<iostream>
using namespace std;

#include<fstream>



void test01()
{
    ofstream ofs;
    ofs.open("test.txt",ios::out);
    
    ofs<<"姓名：张三"<<endl;
    ofs<<"fdsfs"<<endl;
    ofs.close();


    ifstream ifs;
    ifs.open("");
    if(!ifs.is_open()){
        cout<<"文件打开失败"<<endl;
        return;
    }

}



int main(){
    test01();
    return 0;
}