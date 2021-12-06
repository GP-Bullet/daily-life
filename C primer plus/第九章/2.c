#include<stdio.h>

void chline(char ch,int j,int i){
    for(int a=0;a<j;++a){
        for(int b=0;b<i;b++){
            printf("%c",ch);
        }
        printf("\n");
    }
}
int main(){
    char ch;
    int i,j;
    scanf("%c %d %d",&ch,&j,&i);
    chline(ch,j,i);

    return 0;
}
