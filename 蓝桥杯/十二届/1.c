//卡片
#include<stdio.h>
int main(){
    int cnt[10];
    for(int i=0;i<10;i++){
        cnt[i]=2021;
    }
    int i;
    for(i=1;;i++){
        int t=i;        //保存住需要存的数
        //每次提取最后一位数
        while(t){
            int a=t%10;
            if(cnt[a]>0)cnt[a]--;
            else break;
            t/=10;
        }
        
    
    }
    
    return 0;
}