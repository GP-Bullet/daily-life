#include<bits/stdc++.h>


using namespace std;
const int N=110;
int a[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int ans=0,i=0;
        while(i<n){
            int x=m;
            ans++;
        
        while(x>0){
            if(x<a[i]){
                a[i]-=x;
                x=0;
            }else{
                x-=a[i];
                if(x>k){
                    x-=k;
                    i++;
                }else{
                    x=0;
                    i++;
                }
            }
            
        }

        }
        cout<<ans<<endl;
    }
    return 0;   
}