#include<stdio.h>
int main(){
    int i,j;
    int n;
    int sum=0;
    int count=0;

    scanf("%d",&n);

//    1+2+2+3+3+3+4+4+4+4

    for(i=1;;i++){
        for(j=1;j<=i;j++){

            sum=sum+i;
            count++;
//           if(count==n)goto over;
            if(count==n)break;
        }
        if(count==n)break;
    }
    
    
//over:    printf("%d",sum);
        printf("%d",sum);
    return 0;

}
//!被迫用goto
//!或用break层层跳出