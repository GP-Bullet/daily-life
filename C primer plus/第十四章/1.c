#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//结构体
//?strcmp
struct month{    
    char name[15];
    char ab[4];//?
    //留一个位置给\0
    int days;
    int num;
}list[12]=
        {
                {"January", "Jan", 31, 1}, 
                {"February", "Feb", 28, 2}, 
                {"March", "Mar", 31, 3}, 
                {"April", "Apr", 30, 4},
                {"May", "May", 31, 5},
                {"June", "Jun", 30, 6},
                {"July", "Jul", 31, 7},
                {"August", "Aug", 31, 8},
                {"September", "Sep", 30, 9},
                {"October", "Oct", 31, 10},
                {"November", "Nov", 30, 11},
                {"December", "Dec", 31, 12}

        };
int  days(char a[]){
    int sum=0;
    for(int i=0;i<12;i++){
        sum+=list[i].days;
        if(!strcmp(list[i].name,a)){
            return sum;
        }
    }
    return sum;//?
}

int main(){
    printf("%d\n",days("July"));
    printf("%d\n",days("November"));

    return 0;
}        