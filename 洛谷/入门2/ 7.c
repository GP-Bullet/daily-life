/*#include<stdio.h>
int main(){
    char a[14];
    char b[12]=“0123456789X”;
    int i,j;

    
}*/
#include<stdio.h>
int main(){
    char num[14], id[12]="0123456789X",last;
    int sum=0,j=1;
    scanf("%s",num);
    for(int i=0;i<12;i++){
        if(num[i]== '-') continue;
        sum+= (num[i]-'0')*j++;
    }
    last=id[sum%11];
    if(last==num[12]) printf("Right");
    else{
        num[12]=last;
        puts(num);
    }
    return 0;
}