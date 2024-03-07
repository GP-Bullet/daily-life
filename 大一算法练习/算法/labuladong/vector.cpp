#include<iostream>
#include<vector>
using namespace std;

int n=7,m=8;
//空数组
//vector<int> nums;
//n个nums 默认为0
//vector<int> nums(n);

//vector<int> nums{1,3,5};

//vector<int> nums(n,2);

//初始化二维数组
vector<vector<int>> dp;

//初始化一个大小为 m*n 的布尔数组 dp

vector<vector<bool>> dp(m,vector<bool>(n,true));

int n=10;

vector<int> nums(n);

int main(){
    cout << nums.empty();

    cout <<nums.size();
    //在数组尾部插入一个元素20
    nums.push_back(20);
    int b=nums.back();
    cout<<b;//得到最后一个元素

    nums.pop_back();
    //删除最后一个元素

    swap(nums[0],nums[1]);

    int a=nums[4];

}

