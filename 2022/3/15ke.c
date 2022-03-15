
#include<stdio.h>
#include<math.h>
#if 0
int main(){
    float x;
    scanf("%f",&x);
    if(x>=0&&x<10){
        printf("%.2f",sin(x));
    }else if(x>=10&&x<20){
        printf("%.2f",cos(x));
    }else if(x>=20&&x<30){
        printf("%.2f",exp(x)-1);
    }else if(x>=30&&x<40){
        printf("%.2f",log(x+1));
    }else{
        printf("%.2f",pow(x,4));
    }
    return 0;
}
#endif

#if 0
int main(){
    float a;
    scanf("%f",&a);
    if(a<=50){
        printf("%.2f公斤,%.2f元",a,0.15*a);
    }else{
        printf("%.2f公斤,%.2f元",a,50*0.15+(a-50)*0.25);
    }
    return 0;
}
#endif
#include<stdlib.h>
#if 0
int comp(const void*a,const void*b){
    return*(int*)a-*(int*)b;
}
#define n 3
int main(){
    int *a;
    int i;
    a=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++){
        scanf("%d",a+i);
    }
    
    qsort(a,3,sizeof(int),comp);
    
    for(i=0;i<3;i++){
        printf("%d ",a[i]);
    }
    return 0;
}
#endif


#if 0
int main(){
    char a;
    scanf("%c",&a);
    if((int)a>=48&&(int)a<=57){
        printf("%c是数字\n",a);
    }else if((int)a>64&&(int)a<91||(int)a>96&&(int)a<123){
        printf("%c是字母\n",a);
    }else{
        printf("%c是其他字符",a);
    }
    return 0;
}
#endif

#if 0
int main(){
    float x,y;
    scanf("%f,%f",&x,&y);
    float a,b,c,d;
    a=(x-2)*(x-2)+(y-2)*(y-2);
    b=(x+2)*(x+2)+(y-2)*(y-2);
    c=(x+2)*(x+2)+(y+2)*(y+2);
    d=(x-2)*(x-2)+(y+2)*(y+2);
    if(a<=1||b<=1||c<=1||d<=1){
        printf("该点的建筑高度为10m");
    }else{
        printf("该点的建筑高度为0");
    }
    return 0;
}
#endif

#if 0
int main(){
    float a,b;
    int c,d;
    if(scanf("%f+%f",&a,&b)){
        printf("%.2f",a+b);
    }else if(scanf("%f-%f",&a,&b)){
        printf("%.2f",a-b);
    }else if(scanf("%f*%f",&a,&b)){
        printf("%.2f",a*b);
    }else if(scanf("%f/%f",&a,&b)){
        if(b==0){
            printf("0不能做除数");
        }else{
            printf("%.2f",a/b);
        }
    }else if(scanf("%d%%%d",&c,&d)){
        printf("%d",c%d);
    }
    return 0;
}
#endif
#if 0
int main(){
    float a,b;
    char c;
    scanf("%f%c%f",&a,&c,&b);
    switch(c){
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
    return 0;


}
#endif



#if 1;

#endif