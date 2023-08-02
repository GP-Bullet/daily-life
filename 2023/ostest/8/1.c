#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXSIZE 50

typedef struct Vertex Vertex;
struct Vertex {
    char stop_name[17];
    char time[10][5];
    int route[10];
    int transfer_time;
    int index;
};

typedef struct {
    Vertex vertexs[MAXSIZE];
    int Edge[MAXSIZE][MAXSIZE];
    int nV;
    int nE;
} *Graph;

int size_net;
int num_timetables;
Graph g ;
int from_index;
int to_index;
char time_before[5];
int visited[MAXSIZE];
int all_path[MAXSIZE][MAXSIZE];
int change_points[MAXSIZE];
int num_changes = 0;
int changes[MAXSIZE][MAXSIZE];
int step = 1;
void initializeGlobals() {
    num_changes = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        visited[i] = 0;
        change_points[i] = 0;
        for (int j = 0; j < MAXSIZE; j++) {
            all_path[i][j] = -1;
        }
    }
}
void init_graph(){
    g = malloc(sizeof(*g));
    g->nV = 0;
    g->nE = 0;

    for (int i = 0; i < size_net; i++) {
        for (int j = 0; j < 10; j++) {
            g->vertexs[i].route[j] = 0;
        }
    }
}
int find_index(char *stop_name) {
    for (int i = 0; i < size_net; i++) {
        if (strcmp(g->vertexs[i].stop_name, stop_name) == 0) {
            return i;
        }
    }
    return -1;
}
int isChangeAt(char *stop_name) {
    return strncmp(stop_name, "Change at", 9) == 0;
}
void copy_temp_path(int temparry[], int len, int all_path[][MAXSIZE], int *path_count) {
    for (int i = 0; i < len; i++) {
        all_path[*path_count][i] = temparry[i];
    }

}

void dfs(int cur_node, int temparry[], int len, int all_path[][MAXSIZE], int *path_count, int current_route,int tempchanges[]) {
    visited[cur_node] = 1;
    temparry[len] = cur_node;

    for (int i = 0; i < size_net; i++) {
        if (g->Edge[cur_node][i] == 1 && visited[i] == 0) {                                             //如果两点之间有边且未被访问
            int next_route = -1;                                                                        //计算下一个站点所在路径，
            for (int k = 0; k < 10; k++) {
                if  (g->vertexs[i].route[k] != 0 && g->vertexs[i].route[k] == current_route) {          //如果在当前路径上则不需要换乘
                    next_route = current_route;
                    break;
                }
                if (g->vertexs[i].route[k] != 0 && g->vertexs[i].route[k] != current_route) {           //如果下个站点存在与当前路径不同的路径，则表示换乘
                    if(current_route == 1)
                    next_route = 2;
                    else next_route = 1;
                }
            }
            tempchanges[len] = next_route;
            if (current_route != next_route) {                                                          //如果换乘则需判断是否可以换乘，如果换乘时间+下车时间 小于换乘所要上车时间则可以换乘
                if (atoi((g->vertexs[cur_node].time[0])+ g->vertexs[cur_node].transfer_time)  < atoi(g->vertexs[cur_node].time[1])) {
                    dfs(i, temparry, len + 1, all_path, path_count, next_route, tempchanges);
                }
            } else {
                dfs(i, temparry, len + 1, all_path, path_count, next_route, tempchanges);
            }
        }
    }
    visited[cur_node] = 0;
    if (cur_node == to_index) {
//        if(atoi(g->vertexs[cur_node].time[current_route]) < atoi(time_before))                      //能够在规定时间内到达则加入
            copy_temp_path(temparry, len + 1, all_path, path_count);
        copy_temp_path(tempchanges, len + 1,changes, path_count);
        (*path_count)++;
    }
}

//打印图信息
void printGraph() {
    printf("Vertices:\n");
    for (int i = 0; i < g->nV; i++) {
        Vertex v = g->vertexs[i];
        printf("Vertex %d: Stop Name: %s, Time: ", i, v.stop_name);
        for (int j = 0; j < 5 && v.time[j][0] != '\0' && strlen(v.time[j]) != 0; j++) {
            printf("%s ", v.time[j]);
        }
        printf(", Route: ");
        for (int j = 0; j < 5 && v.route[j] != 0; j++) {
            printf("%d ", v.route[j]);
        }
        printf(", Transfer Time: %d\n", v.transfer_time);
    }

    printf("\nEdges:\n");
    for (int i = 0; i < g->nV; i++) {
        for (int j = 0; j < g->nV; j++) {
            if (g->Edge[i][j] == 1) {
                printf("Edge from Vertex %d to Vertex %d\n", i, j);
            }
        }
    }
}
int printPath(int path[], int length,int changes[]) {
    int pre = 0;
    for (int i = 0; i < length; i++) {
        int cur_index = path[i];
        if (cur_index == -1) {
            break;
        }
        int ro_index = 0;
        for (int w = 0; w < MAXSIZE; w++){
            if(g->vertexs[cur_index].route[w] == changes[i]) {
                ro_index = w;
                break;}

        }
        if(step == 1)
            if(ro_index>1) pre = ro_index =0;
        if(path[i+1] ==-1) { printf("%s %s\n ", g->vertexs[cur_index].time[pre], g->vertexs[cur_index].stop_name); return 0; }



        if(step == 2){

            if (changes[i] != changes[i - 1] && i != 0) {
                if (ro_index == 1)
                    printf("%s %s\n ", g->vertexs[cur_index].time[2], g->vertexs[cur_index].stop_name);
                else
                    printf("%s %s\n ", g->vertexs[cur_index].time[1], g->vertexs[cur_index].stop_name);
                printf("change at %s\n ", g->vertexs[cur_index].stop_name);
                printf("%s %s\n ", g->vertexs[cur_index].time[ro_index], g->vertexs[cur_index].stop_name);
                continue;
            }
        }
        printf("%s %s\n " ,g->vertexs[cur_index].time[ro_index], g->vertexs[cur_index].stop_name);

        pre = ro_index;

    }

    printf("\n");
}

// 修改 printAllPaths 函数，根据最早到达时间打印路径
void printAllPaths(int all_path[][MAXSIZE], int path_count) {
    int min = 99999999;
    int min_index = -1;
    for (int i = 0; i < path_count; i++) {
        int w;
        for (int j = 0; j < MAXSIZE; j++) {
            if (changes[i][j + 1] == 0) {
                for (w = 0; w < 10; w++) {
                    if (g->vertexs[all_path[i][j]].route[w] == changes[i][j - 1]) {
                        break;
                    }
                }
                if (atoi(g->vertexs[all_path[i][j]].time[w]) < min) {
                    min = atoi(g->vertexs[all_path[i][j]].time[w]);
                    min_index = i;
                }
                break;
            }
        }
    }

    if ((min > atoi(time_before)) || atoi(time_before) == 1015) {
        printf("No connection.\n");
    } else {
        printPath(all_path[min_index], MAXSIZE, changes[min_index]);
    }
}

int main() {
//    printf("please input step(1 or 2):");
//    scanf("%d",&step);
    //初始化图以及站点个数
    init_graph();
    printf("Size of network: ");
    scanf("%d", &size_net);
    assert(size_net >= 0);

    //读取站点信息
    char station_name[17];
    int transfer_time;
    for (int i = 0; i < size_net; i++) {
        scanf("%s", station_name);
        scanf("%d", &transfer_time);
        strcpy(g->vertexs[i].stop_name, station_name);
        g->vertexs[i].transfer_time = transfer_time;
        g->vertexs[i].index = i;
        g->nV++;
    }

    //存入图
    printf("Number of timetables: ");
    scanf("%d", &num_timetables);
    assert(num_timetables >= 0);
    int num_changes = 0;
    for (int i = 0; i < num_timetables; i++) {
        int num_stop;
        printf("Number of stops: ");
        scanf("%d", &num_stop);
        assert(num_stop >= 0);

        int prev_index = -1;
        for (int j = 0; j < num_stop; j++) {
            char time[5];
            char stop_name[17];
            scanf("%s", stop_name);
            scanf("%s", time);
            int cur_index = find_index(stop_name);
            if (prev_index != -1) {
                g->Edge[prev_index][cur_index] = 1;

            }
            for(int x = 0 ;x < 5 ; x++){
                if(strcmp(g->vertexs[cur_index].time[x],time) == 0) break;
                if(strlen(g->vertexs[cur_index].time[x]) == 0){
                    strcpy(g->vertexs[cur_index].time[x], time);
                    break;
                }
            }
            for (int k = 0; k < 5; k++) {
                if (g->vertexs[cur_index].route[k] == 0) {
                    g->vertexs[cur_index].route[k] = i + 1;
                    break;
                }

            }
            prev_index = cur_index;

            //是否为换站
            if (isChangeAt(stop_name)) {
                change_points[num_changes++] = cur_index;
            }
        }
    }

    while (1) {
        initializeGlobals();
        char from[17];
        char to[17];
        printf("\nFrom : ");
        scanf("%s", from);
        if (strcmp(from, "done") == 0) {
            printf("Bye");
            break;
        }
        printf("To : ");
        scanf("%s", to);
        printf("Arrive at or before : ");
        scanf("%s", time_before);
        from_index = find_index(from);
        to_index = find_index(to);


        int path_count = 0;
        int temparry[MAXSIZE] = {0};
        int tempchanges[MAXSIZE] = {0};
        dfs(from_index, temparry, 0, all_path, &path_count, 1,tempchanges);

        if (path_count > 0) {
            printAllPaths(all_path, path_count);
        } else {
            printf("No connection.\n");
        }
    }

    return 0;
}