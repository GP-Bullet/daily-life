//管理类
//职工抽象类
#pragma once
#include<iostream>
using namespace std;

//职工的分类为：普通员工、经理、老板

//将三种职工抽象到一个类（worker）中,利用多态管理不同职工种类
class WorkerManager
{
public:

	//构造函数
	WorkerManager();

    void Show_Menu();

    void exitSystem();

	//析构函数
	~WorkerManager();

};
