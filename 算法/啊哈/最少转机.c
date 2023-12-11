#include<stdio.h>
struct note
{
    int x;//城市编号
    int s;//转机次数
};
int main(){
    struct note que[2501];
    int e[51][51]={0},book[51]={0};
    int head,tail;
    int i,j,n,m,a,b,cur,start,end,flag=0;
    scanf("%d %d %d %d",&n,&m,&start,&end);
    //初始化二维矩阵
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j)e[i][j]=0;
                else e[i][j]=99999999;
        }
    }
    
    //读入城市之间的航班
    for(i=1;i<=m;i++){
        scanf("%d %d",&a,&b);
        //注意这里是无向图
        e[a][b]=1;
        e[b][a]=1;
    }
    
    //队列初始化
    head=1;
    tail=1;

    //从start号城市出发，将start号城市加入队列
    que[tail].x=start;
    que[tail].s=0;
    tail++;
    book[start]=1;//标记start号城市已在队列中

    //当队列不为空的时候循环
    while(head<tail){
        cur=que[head].x;//当前队列中首城市的编号
        for(j=1;j<=n;j++)
        {
            //从城市cur到城市j是否有航班并且判断城市j是否已经在队列中
            if(e[cur][j]!=99999999 && book[j]==0){
                //如果从城市cur到城市j有航班并且城市j不在队列中，则将j号城市入队
                que[tail].x=j;
                que[tail].s=que[head].s+1;//转机次数+1
                tail++;
                //标记城市j已经在队列中
                book[j]=1;
            }
        }
        //如果到达目标城市，停止扩展，任务结束，退出循环
        if(que[tail-1].x==end){
            //注意下面两句话的位置千万不要写颠倒了
            flag=1;
            break;
        }
        if(flag==1)break;
        head++;//注意这地方，千万不要忘记的当一个点扩展结束后，head++才能继续扩展
    }

    //打印队列中末尾最后一个（目标城市）的转机次数
    //注意tail是指向队列队尾（即最后一位）的下一个位置，所以这需要-1
    printf("%d",que[tail-1].s);

    
    getchar();getchar();
    return 0;
}