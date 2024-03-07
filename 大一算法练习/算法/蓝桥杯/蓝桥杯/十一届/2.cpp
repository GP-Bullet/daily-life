#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int main(){
    ll cnt;
    cin>>cnt;
    cnt/=1000;
    cnt%=86400;
    printf("%02d:%02d:%02d",cnt/3600,cnt/60%60,cnt%60);
	return 0;
}

