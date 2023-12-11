#include<stdio.h>
//边界处理
int main(){
    int n;
    scanf("%d",&n);
    int g[100][100];
    int dx[]={-1,0,1,0};
    int dy[]={0,1,0,-1};
    int x=0,y=0,d=1;

    for(int i=1;i<=n*n;i++){
        g[x][y]=i;
        int a=x+dx[d];
        int b=y+dy[d];
        if(a<0||a>=n||b<0||b>=n||g[a][b]){
            d=(d+1)%4;
            a=x+dx[d];
            b=y+dy[d];
        }
        x=a;
        y=b;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%2d ",g[i][j]);
        }
        printf("\n");
    }

    return 0;
}