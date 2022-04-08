//1
#if 0
#include<stdio.h>
int main(){
    int cnt=0;
    for(int i=1;i<=2020;i++){
        if(i%10==2){
            cnt++;
        }
        if(i/10%10==2){
            cnt++;
        }
        if(i/10/10%10==2){
            cnt++;
        }
        if(i/1000==2){
            cnt++;
        }
    }

    printf("%d",cnt);
    return 0;
//624
}
#endif
//2
#if 0
#include<stdio.h>
int  main(){
    int c;
    int cnt=0;
    for(int i=1;i<=2020;i++){
        for(int j=1;j<=2020;j++){
//求最大公约数  辗转相除法
            int a=i;
            int b=j;

            c=a%b;
            while(c!=0){
                a=b;
                b=c;
                c=a%b;
            }
            if(b==1){
                cnt++;
            }
        }
    }
    printf("%d",cnt);
    return 0;
}
//2481215
#endif


//3
//761

//4
#if 0
#include<stdio.h>
int main(){
    int cnt1=0;
    int cnt2=0;
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        if(a[i]>=60){
            cnt1++;
        }
        if(a[i]>=85){
            cnt2++;
        }
    }
    printf("%.0lf%%\n%.0lf%%",cnt1/(n/100.0),cnt2/(n/100.0));

    return 0;
}
#endif


//5
#if 0
#include<stdio.h>

int main(){
int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    int year,week=6,day,month,sum=0;
    for(year=2000;year<=2020;year++){
        if(year%400==0||(year%4==0&&year%100!=0)){
            a[2]=29;
        }
        for(month=1;month<=12;month++){
            for(day=1;day<=a[month];day++){
                if(day==1||week==1){
                    sum+=2;
                }else{
                    sum+=1;
                }
                week=(week+1)%7;
            
            if(year==2020&&month==10&&day==1){
                printf("%d\n",sum);
                
                return 0;   
            }
            }
            
        }
        a[2]=28;
    }
    return 0;

}
//8879
#endif

#if 0
#include<stdio.h>
int main(){
    long long int n=2021041820210418;
    int cnt=0;
    for(long long int i=1;i*i*i<=n;i++){
        if(n%i==0){
            for(long long int j=i;i*j*j<=n;j++){
                if(n/i%j==0){
                    long long k=n/i/j;
                    if(i==j&&j==k){
                        cnt++;
                    }else if(i==j||i==k||j==k){
                        cnt+=3;
                    }else{
                        cnt+=6;
                    }
                }
            }
        }
    }
    printf("%d",cnt);
}
//2430
#endif

//时间表示
#if 0
#include<stdio.h>
int main(){
    long long int n;
    scanf("%lld",&n);
    n/=1000;
    n%=86400;
    printf("%02lld:%02lld:%02lld",n/3600,n/60%60,n%60);

    return 0;
}
#endif

//砝码称重
#if 1
#include<stdio.h>
int main(){
    
}
#endif