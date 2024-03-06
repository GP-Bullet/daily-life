#include<stdio.h>
struct note {
    int x;
    int y;

};
    char a[20][21];//字符存储地图

int getnum(int i,int j){
    int sum,x,y;
    sum=0;

    //i,j的数值要多次用，为保持i,j在函数中不变，用x和y
    x=i;y=j;
    while(a[x][y]!='#'){
        if(a[x][y]=='G')sum++;
        x--;//继续向上统计
    }
    //向下
    x=i;y=j;
    while(a[x][y]!='#'){
        if(a[x][y]=='G')sum++;
        x++;
    }

    //向左
    x=i;y=j;
    while(a[x][y]!='#'){
        if(a[x][y]=='G')sum++;
        y--;
    }

    x=i;y=j;
    while(a[x][y]!='#'){
        if(a[x][y]=='G')sum++;
        y++;
    }

    return sum;
}

int main(){
    struct note que[401];
    int head,tail;
    int book[20][20]={0};
    int i,j,k,sum,max=0,mx,my,n,m,startx,starty,tx,ty;
    //定义这一大堆

    int next[4][2]={{0,1},
                    {1,0},
                    {0,-1},
                    {-1,0}};

    scanf("%d %d %d %d",&n,&m,&startx,&starty);

    for(i=0;i<=n-1;i++){
        scanf("%s",a[i]);
    }

    head=1;
    tail=1;
    //插入起始坐标
    //坐标分横纵，所以用结构体
    que[tail].x=startx;
    que[tail].y=starty;
    tail++;

    book[startx][starty]=1;
    max=getnum(startx,starty);

    mx=startx;
    my=starty;//这两行干啥
    //记录max的x和y
    //题目无要求则无需

    //
    while(head<tail){
        for(k=0;k<=3;k++){
            //尝试下一个点的坐标
            tx=que[head].x+next[k][0];
            ty=que[head].y+next[k][1];

            //判断是否越界
            if(tx<0||tx>n-1||ty<0||ty>m-1)
                continue;

            //判断是否为平地或者曾经走过
            if(a[tx][ty]=='.'&&book[tx][ty]==0){
                //标记
                book[tx][ty]=1;
                //插入队列     //?
                que[tail].x=tx;
                que[tail].y=ty;
                tail++;

                sum=getnum(tx,ty);
                //update
                if(sum>max){
                    max=sum;
                    mx=tx;
                    my=ty;
                } 
            }
        }
        head++;//必须有

    }

    printf("%d %d %d",mx,my,max);

    return 0;
}