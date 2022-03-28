#include<stdio.h>
    int main()
    {
        int a, b, n = 0;
        scanf("%d %d", &a, &b);
        if(a < 0 ||
 b < 0){
            return 0;
        }
        else{
            for(int i = (a + 1); i < b; ++i){
                int k = 0;
                for(int m = 2; m < i; ++m){
                if(i % m == 0){
                     k = 1;
                    }
                }
                if(0 == k){
                    n++;
                }
            }
        printf("%d", n);
        }
        return 0;
    }