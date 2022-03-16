#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int main(){
    char*c;
    scanf("%s",c);
    if(c[0]=='+'||c[0]=='-'||c[0]=='*'||c[0]=='%'||c[0]=='/'){
        float a,b;
        scanf("%f%%f",&a,&b);
        switch(c[0]){
            case '+':
                printf("%f+%f=%.2f",a,b,a+b);
                break;
            case '-':
                printf("%f-%f=%.2f",a,b,a-b);
                break;
            case '*':
                printf("%f*%f=%.2f",a,b,a*b);
                break;
            case '/':
                    if(b==0){
                        printf("0不能做除数");
                    }else{
                        printf("%f/%f=%.2f",a,b,a/b);
                        break;
                    }
                    
            case '%':
                printf("%d%%%d=%d",(int)a,(int)b,(int)a%(int)b);
                break;
        }
    }else{
        float d;
        scanf("%f",&d);
        if(strcmp("sin",c)==0){
            printf("sin%f=%.2f",d,sin(d));
        }else if(strcmp("cos",c==0)){
            printf("cos%f=%.2f",d,cos(d));
        }else if(strcmp("tan",c)==0){
            printf("tan%f=%.2f",d,tan(d));
        }else if(strcmp("exp",c)==0){
            printf("exp(%f)=%.2f",d,exp(d));
        }else if(strcmp("sqrt",c)==0){
            printf("sqrt%f=%.2f",d,sqrt(d));
        }
    }
    return 0;
}