#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

class Worker
{
public:
    string m_Nam e;
    int m_Salary;
};

void createWorker(vector<Worker>&v)
{
    string nameSeed="ABCDEDFGHIJ";
    
}

void setGroup(vector<Worker>&v,multimap<int,Worker>&m)
{
    for(vector<Worker>::iterator it=v.begin();it!=v.end();it++)
    {
        int deptId =rand()%3;//0 1 2
        m.insert(make_pair(deptId,*it));
}
#define CEHUA 0
#define MEISHU 1

void showWorkerByGroup(multimap<int,Worker>&m)
{
    mutimap<int,Worker>::iterator pos= m.find(CEHUA);
    int count=m.count(CEHUA);
    int index=0;
    for(;pos!=m.end() && index<count ;pos++,index++)
        cout<<"姓名："<< pos->second.m_Name<<"工资"<<pos->second.m_Salary<<endl;
    {
    }
}
int main(){
    vector<Worker>vWorker;
    createWorker(vWorker);

    multimap<int,Worker>mWorer;
}