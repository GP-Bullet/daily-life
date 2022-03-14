/*#include<stdio.h>

int main(){
    int a;
    scanf("%d",&a);
    if(a%60<10){
        printf("%d(m)=%d(h):0%d(m)",a,a/60,a%60);
    }else{
        printf("%d(m)=%d(h):%d(m)",a,a/60,a%60);
    }
    
    return 0;
}
*/

#include<stdio.h>
#include<math.h>

int main(){
    float x1,x2,y1,y2;
    scanf("%f,%f",&x1,&y1);
    scanf("%f,%f",&x2,&y2);
    printf("D=%.2f",pow((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2),0.5));

    return 0;
}
#include<stdio.h>
int main(){
    int a,b,c,d;
    scanf("%d",&a);
    b=a/100;
    c=a/10%10;
    d=a%10;
    printf("%d(8)=%d(10)",a,b*8*8+c*8+d);
    return 0;
}
#include<stdio.h>
int main(){
    char a='a';
    printf("%d\n",a);
    return 0;

}



