#include<stdio.h>
#define MAXVEX 100
typedef struct EdgeNode   //边表结点
{
    int adjvex;  //邻接点，存储下标
    int weight;  // 存储权值
    struct EdgNode *next;  //链域，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode  //顶点表结点  
{
    int in;
    int data;
    EdgeNode *firstedge;    
}VertexNode,AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;      
    int numVertexes,numEdges; //图中当前顶点数和边数
}graphAdjust,*GraphAdjust;

Status Topologicalsort(GraphAdjust GL)
{
    EdgNode *e;
    int i,k,gettop;
    int top=0;        //用于栈指针下标
    int count=0;      // 用于统计输出顶点的个数
    int *stack;       //建栈存储入度为0的顶点
    stack=(int *)malloc(GL->numVertexes*sizeof(int));
    for(i=0;i<GL->numVertexes;i++){
        if(GL->adjList[i].in==0)
            stack[++top]=i;     //将入度为0的顶点入栈
    }
    while(top!=0)
    {
        gettop=stack[top--];  //出栈
        printf(“%d-> ”,GL->adjList[gettop].data);   //打印此顶点
        count++;//统计输出顶点数
        for(e=GL->adjList[gettop].firstedge;e;e=e->next)
        {//对此顶点孤表遍历
            k=e->adjvex;
            
        }

    }
}
