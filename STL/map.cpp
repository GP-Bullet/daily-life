#include<cstdio>
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
#include<cctype>

using namespace std;

map<string,int> cnt;
vector<string> words;

//将单词s进行化成小写
string repr(const string& s){
    string ans =s;
    for(int i=0;i<ans.length();i++){
        ans[i]=tolower(ans[i]);
    }
    sort(ans.begin(),ans.end());
    return ans;
}

int main(){
    int n=0;
    string s;
    while(cin >> s){
        if(s[0]=='#')break;
        words.push
    }
}