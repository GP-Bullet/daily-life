//泛型编程
//函数模板

//类型参数化

#include<iostream>

template<typename T>//声明一个模板，T是一个通用的数据类型
void mySwap(T &a, T &b )
{
    T temp= a;
    a=b;
    b=temp;
}
//函数重载

template<typename T>
void mySwap(T &a, T &b ,T&c)
{
    T temp= a;
    a=b;
    b=temp;
}


//函数模板 如果用自动类型推导 不会发生隐式类型转换 
//如果用    显示指定类型  可以发生类型转换

void test01()
{   
    double a=10.1,b=20.23;

    //两种使用函数模板
    //1.自动类型推导
    mySwap(a,b);
    std::cout<<a<<" "<<b<<std::endl;
}

int main(){
    test01();
    return 0;

}
    
//注意事项       a b 类型一样
//T的类型必须确定

/*
-如果函数模板和普通函数都可以实现，优先调用普通函数
-可以通过空模板参数列表来强制调用函数模板
-函数模板也可以发生重载
-如果函数模板可以产生更好的匹配,优先调用函数模板
*/
mySwap<>(a,b);//强制调用模板


//模板有局限性