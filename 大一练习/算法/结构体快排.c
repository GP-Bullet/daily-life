//永远的聪明王

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct S{
    char subject[2000];
    long int score;
}subject[1001],p,temp;

void Qsort (int left,int right){
    int i,j,t;
    if(left>right){
        return;
    }

    temp=subject[left];
    i=left;
    j=right;
    while(subject[j].score>=temp.score&&i<j){
        j--;
    }

    while(subject[i].score<=temp.score&&i<j){
        i++;
    }
    if(i<j){
        p=subject[i];
        subject[i]=subject[j];
        subject[j]=p;
    }
    subject[left]=subject[i];
    subject[i]=temp;

    Qsort(left,i-1);
    Qsort(i+1,right);
}
int main(){
    long int num=0;
    scanf("%ld",&num);

    struct S t;
    for(long int i=1;i<=num;++i){
        scanf("%s %ld",subject[i].subject,&subject[i].score);
    }

    Qsort(1,num);

    for(long int i=1;i<=num;i++){
        printf("%s ",subject[i].subject);
    }

    return 0;

}



