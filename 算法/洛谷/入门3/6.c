#include<stdio.h>
int main(){
    int n,x,i;
    int count=0;
    scanf("%d %d",&n,&x);

/*一种思路
    for(i=1;i<=9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                if(k==x)count++;
                if(j==x)count++;
                if(i==x)count++;
            }
        }
    }

//或从字符的角度考虑呢？
//计算每一位的方法
12%10=2
12/10%10=1
123/10/10%10=1
*/    
int temp;
    for(i=1;i<=n;i++){
        temp=i;
        while(temp>0){
        if(temp%10==x)count++;
        temp=temp/10;
        }
    }
    printf("%d",count);
    return 0;
    }



