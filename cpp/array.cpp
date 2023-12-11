/*
!constexpr
string strs[get_size()];  

!内置类型
!引用    与    对象

!！！！！！！！！怎么深挖编译器


理解复杂的数组声明

使用数组的时候编译器会把它转换成指针

#Include<iterator>

类比迭代器 
    int ia[]={0,1,2,3,4,5,6,7,8,9};
    int *beg=begin(ia);
    int *last=end(ia);

!内置下标运算可以为负值


C风格字符串不要用了
*/
#include<iostream>
#include<vector>
#include<iterator>
using namespace std;

int main(){
    /*
    *1
    const int size=10;
    int arr[size];
    for(auto it=arr;it!=arr+size;it++){
        *it=0;
    }
    for(auto i:arr){
        cout <<i<<" ";
    }

    cout<<endl;
    */
    /*
    *2
    vector<int>v={0,1,2,3,4,5,6,7,8,9};
    int arr[10];
   // for(auto it=arr;it!=arr+10;it++){
    //    *it=
    //}
    for(int i=0;i!=v.size();i++){
        arr[i]=v[i];
    }
    */

    //数组给vector赋值

    int arr[]={0,1,2,3,4,5,6,7,8,9};
    vector<int>v(begin(arr),end(arr));

    for(auto i:v){
        cout<< i <<" ";
    }
    cout<<endl;
    
    return 0;
}