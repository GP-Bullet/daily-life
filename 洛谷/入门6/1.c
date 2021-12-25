#include<stdio.h>
#include<math.h>



struct note{
    double x;
    double y;
}; 
int main(){
    int i;
    struct note dian[3];
    for(i=0;i<3;i++){
        scanf("%lf %lf",&dian[i].x,&dian[i].y);
    }
    double sum=0;
    sum=sum+sqrt((dian[0].x-dian[1].x)*(dian[0].x-dian[1].x)+(dian[0].y-dian[1].y)*(dian[0].y-dian[1].y));
    sum=sum+sqrt((dian[0].x-dian[2].x)*(dian[0].x-dian[2].x)+(dian[0].y-dian[2].y)*(dian[0].y-dian[2].y));
    sum=sum+sqrt((dian[1].x-dian[2].x)*(dian[1].x-dian[2].x)+(dian[1].y-dian[2].y)*(dian[1].y-dian[2].y));

    printf("%.2lf",sum);

    return 0;
}