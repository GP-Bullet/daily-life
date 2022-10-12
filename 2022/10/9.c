//随机生成迷宫
在当前位置寻找四个方位中的可走方块。
若当前试探方位可走。则将该试探方位的方块入栈，并将此时走过的方块置为不可走（这里将值置为-1），以防止两个方块来回进入死循环，此时试探方位的方块在栈的顶部，再用栈顶方块继续对四个方位进行试探。
若当前方块的四个试探方位都无法前进。则将当前方块退栈，并将退栈方块的值恢复为0，然后找此时栈顶方块的其他可能的相邻方块

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<math.h>

//地图长度L，包括迷宫主体40，外侧的包围的墙体2，最外侧包围路径2（之后会解释）
#define L 44
 
//墙和路径的标识
#define WALL  0
#define ROUTE 1
 
//控制迷宫的复杂度，数值越大复杂度越低，最小值为0
static int Rank = 0;
 
//生成迷宫
void CreateMaze(int **maze, int x, int y);
 
int main(void) {
    srand((unsigned)time(NULL));
 
    int **Maze = (int**)malloc(L * sizeof(int *));
    for (int i = 0; i < L; i++) {
        Maze[i] = (int*)calloc(L, sizeof(int));
    }
 
    //最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
    for (int i = 0; i < L; i++){
        Maze[i][0] = ROUTE;
        Maze[0][i] = ROUTE;
        Maze[i][L - 1] = ROUTE;
        Maze[L - 1][i] = ROUTE;
    }
 
    //创造迷宫，（2，2）为起点
    CreateMaze(Maze, 2, 2);
 
    //画迷宫的入口和出口
    Maze[2][1] = ROUTE;
 
    //由于算法随机性，出口有一定概率不在（L-3,L-2）处，此时需要寻找出口
    for (int i = L - 3; i >= 0; i--) {
        if (Maze[i][L - 3] == ROUTE) {
            Maze[i][L - 2] = ROUTE;
            break;
        }
    }
 
    //画迷宫
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (Maze[i][j] == ROUTE) {
                printf("  ");
            }
            else {
                printf("墙");
            }
        }
        printf("\n");
    }
 
    for (int i = 0; i < L; i++) free(Maze[i]);
    free(Maze);
 
    system("pause");
    return 0;
}
 
void CreateMaze(int **maze, int x, int y) {
    maze[x][y] = ROUTE;
 //确保四个方向随机
    int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = direction[0][0];
        direction[0][0] = direction[r][0];
        direction[r][0] = temp;
 
        temp = direction[0][1];
        direction[0][1] = direction[r][1];
        direction[r][1] = temp;
    }
 
    //向四个方向开挖
    for (int i = 0; i < 4; i++) {
        int dx = x;
        int dy = y;
 
        //控制挖的距离，由Rank来调整大小
        int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
        while (range>0) {
            dx += direction[i][0];
            dy += direction[i][1];
 
            //排除掉回头路
            if (maze[dx][dy] == ROUTE) {
                break;
            }
 
            //判断是否挖穿路径
            int count = 0;
            for (int j = dx - 1; j < dx + 2; j++) {
                for (int k = dy - 1; k < dy + 2; k++) {
                    //abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
                    if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
                        count++;
                    }
                }
            }
 
            if (count > 1) {
                break;
            }
 
            //确保不会挖穿时，前进//确保四个方向随机
    int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = direction[0][0];
        direction[0][0] = direction[r][0];
        direction[r][0] = temp;
 
        temp = direction[0][1];
        direction[0][1] = direction[r][1];
        direction[r][1] = temp;
    }
 
    //向四个方向开挖
    for (int i = 0; i < 4; i++) {
        int dx = x;
        int dy = y;
 
        //控制挖的距离，由Rank来调整大小
        int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
        while (range>0) {
            dx += direction[i][0];
            dy += direction[i][1];
 
            //排除掉回头路
            if (maze[dx][dy] == ROUTE) {
                break;
            }
 
            //判断是否挖穿路径
            int count = 0;
            for (int j = dx - 1; j < dx + 2; j++) {
                for (int k = dy - 1; k < dy + 2; k++) {
                    //abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
                    if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
                        count++;
                    }
                }
            }
 
            if (count > 1) {
                break;
            }
 
            //确保不会挖穿时，前进
            --range;
            maze[dx][dy] = ROUTE;
        }
 
        //没有挖穿危险，以此为节点递归
        if (range <= 0) {
            CreateMaze(maze, dx, dy);
        }
    }
}
            --range;
            maze[dx][dy] = ROUTE;
        }
 
        //没有挖穿危险，以此为节点递归
        if (range <= 0) {
            CreateMaze(maze, dx, dy);
        }
    }
}

