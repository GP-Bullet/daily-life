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


//!迭代器容器都可以用 ， for循环中 用！=更多迭代器的！= 


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
    //无须知道迭代器的精准类型

    //!常量指针


//!迭代器只读不写最好使用常量类型（const_iterator）得到     cbegin cend

    //auto it3=v.cbegin
    //!(*it).empty()   == it->empty

    //!但凡是使用了迭代器的循环体，都不要向迭代器所述的容器添加元素
/*
! string和vector有更多迭代运算
    auto mid=vi.begin()+vi.size()/2;
    difference_type
    

*/
    
}