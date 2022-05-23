#include<stdio.h>
#include<string.h>
void wanshu(){
    int num[1000];
    int sum,t;
    memset(num,0,1000);

    for(int i = 1; i<1000; i++)
    {  
        t = 0;
        sum = 0;
        for(int n = 1; n<i; n++)
            if(i/n*n == i)
                num[t++] = n;
        
        for(int i = 0; i<t; i++)
            sum += num[i];

        if(sum == i)
            printf("%d\n",i);
    }

} 
int main(){
    wanshu();
    return 0;
}