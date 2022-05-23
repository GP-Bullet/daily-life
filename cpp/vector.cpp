#include<vector>
#include<cstdio>
#include<iostream>
using namespace std;
//访问对象中的元素的方法和string差不多

/*
vector<int>v{1,2,3,4,5,6,7,8,9};

int main(){
    for(auto &i:v){
        i*=i;
    }
    for(auto i: v)
        cout << i<< " ";
    cout<<endl;
}


vector<unsigned>scores(11,0);
int main(){
    unsigned grade;
    while(cin>>grade){
        if(grade<=100)
            ++scores[grade/10];
    }
}
添加元素
for(decltype(ivec.size())ix=0;ix!=10;++ix){
    ivec.push_back(ix);//
}*/

//迭代器容器都可以用 ， 


int main(){
    /*
    if(s.begin() !=s.end()){//确保s非空
        auto it =s.begin();
        
        *it=toupper(*it);
    }*/string s("some thing");
    //遇到空白也停
    for(auto it=s.begin();it!=s.end()&& !isspace(*it);++it){
        *it=toupper(*it);
    }
    cout<<s<<endl;
}