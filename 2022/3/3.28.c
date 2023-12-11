#include<stdio.h>
    int main()
    {
        int a, b, n = 0;
        scanf("%d %d", &a, &b);
<<<<<<< HEAD
        if(a < 0 ||b < 0){
=======
        if(a < 0 ||
 b < 0){
>>>>>>> 89f2751646061e5b8fadaedef18aa01d1da219f7
            return 0;
        }
        else{
            for(int i = (a + 1); i < b; ++i){
                int k = 0;
                for(int m = 2; m < i; ++m){
                if(i % m == 0){
<<<<<<< HEAD
                k = 1;
=======
                     k = 1;
>>>>>>> 89f2751646061e5b8fadaedef18aa01d1da219f7
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