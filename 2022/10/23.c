#include<stdio.h>
void test(int *b){
    printf("%d",b[0]);
}
int main(){
    int a[2]={1,2};
    test(a);
    return 0;
}