//卡片



//?想想跑出来的结果是不是想要的最终结果
#include<stdio.h>
int main(){
    int cnt[10];
    for(int i=0;i<10;i++){
        cnt[i]=2021;
    }
    //跳出多层循环
    for(int i=1;;i++){
        int t=i;        //保存住需要存的数
        int  a=0;   //每次提取最后一位数
        while(t){
            a=t%10;//l临时处理
            if(cnt[a]>0)cnt[a]--;
            else break;
            t/=10;
        }
        if(!(cnt[a]>0)){
            printf("%d ",i);
            break;
        }    
    }
    return 0;
}

//3182-1=3181