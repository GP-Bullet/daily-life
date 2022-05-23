//二分搜索    和确定零点思路一样


//!  什么都能用auto吗


//! 迭代器操作类似与指针
#include<string>
#include<iostream>
#include<vector>

using namespace std;
/*

练习3.26：在100页的二分搜索程序中，为什么用的是mid=beg +( end - beg ) / 2，而非mid = ( beg + end )/2; ？
答：mid、beg、end都属于同类型的迭代器，两个迭代器相减 ( beg + end )的结果是它们之间的距离，其结果不是迭代器。
而迭代器加上一个整数（ beg +( end - beg ) / 2 ）仍然是一个迭代器，只不过位置向前或向后移动了。



int main(){
    vector<int> text={1,3,5,7,9,11,15,19};
    auto beg=text.begin(),end=text.end();
    auto mid=text.begin()+text.size()/2;
    auto sought=3;
    while(mid!=end&&*mid!=sought){
        if(sought<*mid)
            end=mid;
        else
            beg=mid+1;
        mid=beg+(end-beg)/2;
    }
    
    
}
    */

int main(){
    vector<unsigned> score(11,0);
    unsigned grade;
    while(cin>>grade){
        if(grade<=100)
            ++*(score.begin()+grade/10);
    }
    for(auto s:score){
        cout<<s<<endl;
    }

    return 0;
}