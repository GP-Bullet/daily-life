#include<stdio.h>
int main(){
    int a,n,i;
    int sum=0;
    scanf("%d %d",&a,&n);
    for(i=0;i<n;i++){
        if(a==1||a==2||a==3||a==4||a==5){
            sum=sum+250;
        }
        if(a==7){
            a=a-7; 
        }a++;
    }


        
    printf("%d",sum);

    return 0;
    
}