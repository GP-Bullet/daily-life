#include<stdio.h>
struct note{
    int x;//横坐标
    int y;//纵坐标
    int f;//父亲在队列中的编号
    int s;//步数
};

int main(){
    struct note que[2501];//地图最大50*50
    int a[51][51]={0};int book[51][51]={0};

    //表示走的方向的数组
    int next[4][2]={{0,1},//right
                    {1,0},//down
                    {0,-1},//left
                    {-1,0}};//up
    
    int head,tail;
    int i,j,k,n,m,startx,starty,p,q,tx,ty,flag;

    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    
    scanf("%d %d %d %d",&startx,&starty,&p,&q);

    //队列初始化
    head=1;
    tail=1;
    //往队列插入迷宫入口坐标
    que[tail].x=startx;
    que[tail].y=starty;
    que[tail].f=0;
    que[tail].s=0;
    tail++;
    book[startx][starty]=1;

    flag=0;//标记是否到达目标点
    //队列不为空循环
    while(head<tail){
        //枚举4个方向
        for(k=0;k<3;k++){
            //计算下一个点的坐标
            tx=que[head].x+next[k][0];
            ty=que[head].y+next[k][1];
            //判断是否越界
            if(tx<1||tx>n||ty<1||ty>m)
                continue;
            //判断是否是障碍物或者已经在路径中
            if(a[tx][ty]==0&&book[tx][ty]==0){
                //把这个点标记为已经走过
                //宽搜不需将book还原
                book[tx][ty]=1;
                //插入新的点到队列中
                que[tail].x=tx;
                que[tail].y=ty;
                que[tail].f=head;//

                que[tail].s=que[head].s+1;//步数是父亲步数+1
                tail++;
            }

            //如到目标点，停止扩展，任务结束，退出循环
            if(tx==p && ty==q){
                flag=1;
                break;
            }
        }
        if(flag==1)break;

        head++;
    }

    //打印最后一个点步数
    //tail-1
    printf("%d",que[tail-1].s);


    return 0;

}


