#include<stdio.h>

int main()
    {
        int arr[100];
        printf("Enter the number of the num you want to enter:\n");
        int n;
        scanf("%d", &n);
        printf("Enter your array\n");
        for(int i = 0; i < n; ++i){
            scanf("%d", &arr[i]);
        }
        int t;
        for(int i = 0; i < n / 2; i++){
            t = arr[i]; arr[i] = arr[n - i - 1]; arr[n - i - 1] = t;
        }
        for(int i = 0; i < n; ++i){
            printf("%d ", arr[i]);
        }
        return 0;
    }