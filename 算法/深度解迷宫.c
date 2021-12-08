#include<stdio.h>
int n,m,p,q,min=99999999;
int a[51][51],book[51][51];
void dfs(int x,int y,int step){
    int next[4][2]={{0,1},//right
                    {1,0},//down
                    {0,-1},//left
                    {-1,0}};//up
    
    int tx,ty,k;
    //判断
    if(x==p && y==q){
        //update min
        if(step<min)
            min=step;
        return;
    }

    //枚举4种走法
    for(k=0;k<=3;k++){
        tx=x+next[k][0];
        ty=y+next[k][1];

        //是否越界
        if(tx<1||tx>n||ty<1||ty>m)
            continue;
        //判断是否为障碍物或者已经在路径中
        if(a[tx][ty]==0&&book[tx][ty]==0){
            book[tx][ty]=1;//标记
            dfs(tx,ty,step+1);//尝试下一个点
            book[tx][ty]=0;//取消标记
        }
    }
    return;
}

int main(){
    int i,j,startx,starty;

    //读入n和m,n为行，m为列
    scanf("%d %d",&n,&m);

    //读入迷宫
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    //读入起点和终点坐标
    scanf("%d %d %d %d",&startx,&starty,&p,&q);

    //从起点开始搜索
    book[startx][starty]=1;//标记

    dfs(startx,starty,0);

    //输出最短步数
    printf("%d",min);
    getchar();getchar();

    return 0;
}