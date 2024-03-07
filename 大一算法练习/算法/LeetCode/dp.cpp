#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.size();
        if(n<2){
            return s;
        }
        
        int maxLen=1;
        int begin=0;
        // dp[i][j] 表示 s[i..j] 是否是回文串
        vector<vector<int>> dp(n, vector<int>(n));
        // 初始化：所有长度为 1 的子串都是回文串
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        //递推开始
        //先枚举子串长度
        for(int L=0;L<=n;L++){//长度先限定
            //枚举左边界
            for(int i=0;i<n;i++){//i要移动
                //L和i确定右边界
                int j=i+L-1;
                if(j>=n)break;
            
                if(s[i]!=s[j]){
                    dp[i][j]=false;
                }else{
                    if(j-i<3){
                        dp[i][j]=true;
                    }else{
                        dp[i][j]=dp[i+1][j-1];//再看看里面
                }
            }
            if(dp[i][j]&&j-i+1>maxLen){
                maxLen=j-i+1;
                begin=i;//记录子串的起始点
            }
        }
        
        }
        return s.substr(begin,maxLen);
    }
    
};