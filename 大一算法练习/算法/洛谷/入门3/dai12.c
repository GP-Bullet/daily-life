#include<stdio.h>
#include<math.h>

int main(){
    double a;
    scanf("%lf",&a);

    int i=1.0;
    double sum=2.0;
    while(sum<=a){
        sum=sum+2*pow(0.98,i);
        i++;
    }


    printf("%d",i);
    return 0;
}