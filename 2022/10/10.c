#include<stdio.h>

void test(int arry[a][b],int a,int b){
    for(int i = 0 ; i < a ;i++){
        for(int j = 0 ; j < b ; j++){
            printf("%d\t",arry[i][j]);
        }
        printf("\n");
    }
}
int main(){

    int arry[3][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
    test(arry,3,5);
    return 0;
}