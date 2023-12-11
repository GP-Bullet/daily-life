/*

动态规划
求最值 最长递增子序列 最小编辑距离
核心问题是穷举 所有可行的答案穷举求最值

存在重叠子问题 需要 备忘

递归
递归的理解是先往下一层层传递，当碰到终止条件的时候会反弹，最终会反弹到调用处。
        
return返回的是上一次调用的位置

*/
#include<iostream>
using namespace std;
#include<vector>
int helper(vector<int>&memo,int n){
    //base case
    if(n==1||n==2)return 1;
    //已经计算过
    if(memo[n]!=0)return memo[n];
    memo[n]=helper(memo,n-1)+helper(memo,n-2);
    return memo[n];
}
    int fib(int N){
        if(N==0)return 0;
        //全初始化成0
        vector<int>memo(N+1,0);
        //进行带备忘录的递归
        return helper(memo,N);
    }                                                                                                                                                                                                                                                           


//这么看 动态规划甚至更好想
int fib2(int N){
    if(N==0)return 0;
    if(N==1||N==2)return 1;
    vector<int>dp(N+1,0);
    //base case
    dp[1]=dp[2]=1;
    for(int i=3;i<=N;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[N];
}


//如果对空间有要求可以再优化

//状态压缩

int fib3(int N){
    if(N==0)return 0;
    if(N==2||N==1)return 1;
    int prev=1,curr=1;
    for(int i=3;i<=N;i++){
        int sum=prev+curr;
        prev=curr;
        curr=sum;
    }
    return curr;
}

//最优子结构
//凑零钱问题

int coinChange(vector<int>&coins,int amount){
    vector<int>dp(amount+1,amount+1);
    dp[0]=0;

    for(int i=0;i<dp.size();i++){
        for(int coin:coins){
            if(i-coin<0)continue;
            dp[i]=min(dp[i],1+dp[i-coin]);
        }
    }
    return(dp[amount]==amount+1)?-1:dp[amount];
}