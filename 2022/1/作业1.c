//1

#include<stdio.h>
#include<math.h>
int main(){
    float a;
    scanf("%f",&a);
    printf("%f %f",fabs(a),a*a);
    return 0;
}

//2

#include<stdio.h>
int main(){
    int a,b,c,d;
    
    scanf("%d %d %d %d",&a,&b,&c,&d);
    float e=(a+b+c+d)/4;
    printf("%.2f\n",e);
    return 0;
}
//3

#include<stdio.h>
int main(){
    char a,b,c;
    scanf("%c%c%c",&a,&b,&c);
    printf("%c%c%c\n",c,b,a);
    return 0;
}

//4
#include<stdio.h>
int main(){
    int a,b,c,d,max;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    max=a;
    if(b>max)max=b;
    if(c>max)max=c;
    if(d>max)max=d;
    printf("%d\n",max);
}
//5
#include<stdio.h>
int main(){
    int a,b,c,d,min;
    scanf("%d %d %d %d",&a,&b,&c,&c,&d);
    min=a;
    if(b<min)min=b;
    if(c<min)min=c;
    if(d<min)min=d;
    printf("%d\n",min);
    return 0;
}
