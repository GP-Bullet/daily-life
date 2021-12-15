/*//阶乘
//高精度算法
#include<stdio.h>
int main(){
    int n,sum1=0,sum2=0;
    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        for(int j=1;;j++){
            sum1=j*++j;
        }
        sum2=sum2+sum1;
    }
    printf("%d",sum2);
    return 0;

}

//高精度算法学习
//加法，注意进位
#include<stdio.h>
#include<string.h>
int main(){
    char s[10100];char ss[10100];
    int a[10100]; int b[10100];
    int len;
    scanf("%s",s);
    scanf("%s",ss);//疑问：为什么先用字符型--整形数组不能直接存一串
                    //为啥要把数反过来--进位时好进位
    
    int l1=strlen(s);
    int l2=strlen(ss);//求最长的长度
    if(l1>l2){
        len=l1;
    }else{
        len=l2;
    }

    for(int i=l1-1;i>=0;i--) {
        a[l1-i-1]=s[i]-'0';
    }                           //两个for循环是将输入的两个字符串倒过来
    for(int i=l2-1;i>=0;i--){ //再将字符串里的字符转换为数字赋值给a,b整型数组 
        b[l2-i-1]=ss[i]-'0';
    } 

    for(int i=0;i<len;i++){
        a[i]=a[i]+b[i];
        a[i+1]=a[i+1]+a[i]/10;//考虑进位
        a[i]=a[i]%10;
    }
    

    if(a[len]!=0) len++;//考虑是否最高位进位
    //倒着输出
    for(int i=len-1;i>=0;i--){
        printf("%d",a[i]);
    }    
    return 0;
    
}


//高精度减法
//考虑大数减小数还是小数减大数（正负号）--都让大数减小数最后补正负号
                                //
//借位

#include<stdio.h>
#include<string.h>

int main(){
    int flag=0;
    int len;
    char s[10100]; char ss[10100];
    int a[10100]; int b[10100];
    scanf("%s",s);scanf("%s",ss);
    int i;
    int l1=strlen(s);
    int l2=strlen(ss);
    if(l1>l2){
        len=l1;
    }else{
        len=l2;
    }


    if(l1<l2||(l1==l2&&strcmp(s,ss)<0){
            flag=1;
        for(int i=0;i<l2;i++){
            a[l2-1-i]=ss[i]-'0';
        }
        for(int i=0;i<l1;i++){
            a[l1-1-i]=s[i]-'0';
        }
    }else
        for(int i=0;i<l1;i++){
            a[l1-1-i]=s[i]-'0';
        }
        for(int i=0;i<l2;i++){
            a[l2-1-i]=ss[i]-'0';
        }
    


    for(int i=0;i<len;i++){
        a[i]=a[i]+10-b[i];//每个都借
        a[i+1]=a[i]-a[i]/10;
        a[i]=a[i]%10;
    }
        while(a[len-1]==0&&len>1)len--;//while去零法

        if(flag=1)printf("-");

        for(int i=len-1;i>0;i--){
            printf("%d",a[i]);    
        }
    return 0;


}


//高精度乘法（低乘高）
//注意进多位


//运算
//a[i] = a[i] * d + jinwei;    //运算 
//		jinwei = a[i] / 10;      //进位 
//		a[i] %= 10;
*/
#include<stdio.h>
int main(){ 
}














