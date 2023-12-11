//全部素数因子
#include <stdio.h>
#include <math.h>

int is_prime(int t)
{
    for (int i = 2; i <= sqrt(1.0 * t); i++)
        if (t % i == 0)
            return 0;
    return 1;
}

int main() {
    int a;
    scanf("%d",&a);
    for(int i=2;i<=a;i++){
        int n =i;
        while((a%n) ==0){ 
            if(is_prime(n)) printf("%d ",n);  
            a=a/n;
        }
    }
    return 0;
}
