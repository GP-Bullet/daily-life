#include<stdio.h>
#include<math.h>

#if 0
int main(){
    double x;
    scanf("%lf",&x);
    if(x>10){
        x=log(x+3);
    }else if(x>-3&&x<=10){
        x=exp(x);
    }else{
        x=sin(x)/(cos(x)+4);
    }
    printf("%.2lf",x);
    return 0;
}
#endif

#if 0
int main(){
    int a,b;
    scanf("%d:%d",&a,&b);
    if(a<11||(a==12&&b==0)){
        printf("%02d:%02d AM",a,b);
    }else if(a==12&&b!=0){
        printf("%02d:%02d PM",a,b);
    }else{
        printf("%02d:%02d PM",a-12,b);
    }
    
    return 0;
}
#endif


#if 0
int main(){
    int a,b;
    scanf("%d,%d",&a,&b);
    if(a==0||b==0){
        return 0;
    }else{
        if(!(a%2)&&!(b%2)){
            printf("%d+%d=%d",a,b,a+b);
        }
        if((a%2)&&(b%2)){
            printf("%d-%d=%d",a,b,a-b);
        }
        if((a%2)&&!(b%2)){
            printf("%d*%d=%d",a,b,a*b);
        }
        if(!(a%2)&&(b%2)){
            printf("%d/%d=%d",a,b,a/b);
        }
        return 0;
    }
    
}
#endif
#if 1
int main(){
    int a;
    scanf("%d",&a);
    if(a<=0){
        return 0;
    }else{
        if(!(a%3)&&(a%5)){
            printf("%d",a%5);
        }
        if(!(a%5)&&(a%3)){
            printf("%d",a%3);
        }
        if(a%5!=0&&a%3!=0){
            printf("%d",a%15);
        }
    }
    return 0;
}

#endif