#include<stdio.h>
int main(){
    int a,b,c;
    char d,e,f;
    scanf("%d  %d %d",&a,&b,&c);
    scanf("%c %c %c",&d,&e,&f);
//六种情况好麻烦
    if(d>e>f)
    if(d>f>e)
    if(e>d>f)
    if(e>f>d)
    if(f>e>d)
    if(f>d>e)



    printf(%d %d %d,a,b,c);

    return 0;
}