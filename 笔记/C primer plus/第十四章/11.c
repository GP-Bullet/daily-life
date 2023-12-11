#include<stdio.h>
#include<math.h>

int transform(double *source,double *target,int n,double (*pfun)(double x));
void print_results(const double*source,int n);

int main(){
    double source[4]={1,2,3,4};
    double target[4]={0};

    transform(source,target,4,sin);
    puts("source:");
    print_results(source,4);
    puts("target:");
    print_results(target,4);

    return 0;
}

int transform(double *source,double *target,int n,double (*pfun)(double x)){
    int i=0;

    for(i=0;i<n;i++){
        target[i]=pfun(source[i]);

        return i;
    }
}

void print_results(const double*source,int n){
    for(int i=0;i<n;i++){
        printf("%lf",source[i]);
    }
    putchar('\n');
}