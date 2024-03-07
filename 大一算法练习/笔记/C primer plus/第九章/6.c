#include<stdio.h>
void max(double *a,double *b,double *c);
int main(){
    max(&a,&b,&c);
}
void max(double *a,double *b,double *c){
    double t;
    if(*a>*b){
        t=*a;
        *a=*b;
        *b=t;
    }
    if(*a>*c){

    }
    if(*b>*c){

    }

}