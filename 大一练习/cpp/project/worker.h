
//职工的属性为：职工编号、职工姓名、职工所在部门编号

//职工的行为为：岗位职责信息描述，获取岗位名称

//创建文件worker.h 文件并且添加如下代码：
//职工抽象基类
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:

	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_Id; //职工编号
	string m_Name; //职工姓名
	int m_DeptId; //职工所在部门名称编号
};
