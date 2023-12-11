#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void*a,const void*b)
{
    return strcmp((char*)a,(char*)b);
}
void Input(char* a[6]){

    for(int i=0;i<6;i++){
        scanf("%s",a[i]);
    }
}
void sort(char* a[6]){
    qsort(a,6,100,cmp);
}
void Output(char* a[6]){
    for(int i=0;i<6;i++){
        printf("%s\n",a[i]);
    }
}
int main(){
    char *a[6];
    Input(a);
    sort(a);
    Output(a);

    return 0;
} 