#include<string>
#include<iostream>
using namespace std;

int main(){

/* string s1;
    string s2;
    cin>>s1>> s2;
    cout<<s1<<'\n'<<s2<<endl;//输出流

    //读取未知数量
    string word;
    while(cin>>word){
        cout<<word<<endl;
    }
    
//为什么会结束，为什么会换行
//?endl*/
/*


    //getline 保留空白符
    string line;
    //每次读入一整行，直至到达文件末尾

    //

    while(getline(cin,line)){
        if(!line.empty()&&line.size()<10){//只输出非空的行
            cout<<line<<endl;
        }
        
    }
    
//?一整行有多大

//比较string
//赋值
//相加

//?\n  \0有没有

    string s1="hello,   ",s2="world";
    string s3=s1+s2;
    cout<<s3<<endl;
    s1+=s2;
    cout<<s1<<s2<<endl;
    s2+=s1;
    cout<<s1<<endl<<s2;
    s1=s2;
    cout<<s1<<endl<<s2;




#include<cctype>
//处理每个字符,范围for
string s = "ab\0c";
string s1="c";
cout<<s + s1;






//?字符串字面值与string

//*处理string中的字符
    string str("some string");
    for(auto c:str){
        cout << c << endl;

    }
    for(int i=0;;i++){
        if(str[i]=='\0'){
            cout<<"lalalla"<<endl;
            break;
        }
        cout<<str[i]<<endl;
    }
    char str1[20]="some string";
    for(int i=0;str1[i]=='\0';i++){
        printf("%c ",str[i]);
    }
    return 0;
!啊到底有没有\0*/

    string s("Hello World!!!");
    for(auto &c:s)
        c=toupper(c);
    cout<< s << endl;


    using S =string;
    S a("hello");
    cout<<a<<endl;
    
//处理一部分字符 下标 或者迭代器
//size返回一个无符号整型数
//使用下标访问空string引发不可预知结果

}