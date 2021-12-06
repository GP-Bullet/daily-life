/*
#include <stdio.h>
#include <stdlib.h>
 
void large_of(double *a, double *b)
{
    *a > *b ? b = *a : a = *b;
}
int main(void)
{
    double a, b;
    scanf("%lf %lf", &a, &b);//注意参数是指针
    large_of(&a, &b);
    printf("%lf %lf\n", a, b);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
void large_of(double * x,double * y);
int main()
{
    double x,y;
    printf("Enter two number:\n");
    scanf("%lf %lf",&x,&y);
    printf("Originally, x=%lf, y=%lf\n",x,y);
    large_of(&x,&y);
    printf("Now, x=%lf, y=%lf\n",x,y);
    
    return 0;
}
void large_of(double * x,double * y){
    double back;
    if(*x>*y)
      *y=*x;
    else
      *x=*y;
}*/
#include<stdio.h>
void larger_of(double *x,double *y){
    (*x>*y)?(*y=*x):(*x=*y);//不加括号会出错的
   /* if(*x>*y)
      *y=*x;
    else
      *x=*y;*/

}
int main(){
    double x,y;
    scanf("%lf %lf",&x,&y);
    larger_of(&x,&y);
    printf("%lf %lf",x,y);

    return 0;
}