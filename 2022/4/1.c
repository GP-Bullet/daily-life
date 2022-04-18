#include<stdio.h> //move left
#include <stdlib.h>
int main()
    {
        int n, m, arr[1000], *p = NULL;
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; ++i){
            scanf("%d", &arr[i]);
        }
        for(int k = 0; k < m; ++k){
            p = &arr[0];
            int t = arr[0];
            for(int I = 0; I < n - 1; ++I){
                *(p + I) = *(p + I + 1);
                }
            arr[n - 1] = t;
        }
        int count = 0;
        for(int II = 0; II < n; ++II){
            printf("%d", arr[II]);
            ++count;
            if(count < n) printf(" ");
        }
        return 0;
        free(p);
        p = NULL;
    }