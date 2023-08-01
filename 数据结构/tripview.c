/*
 * The complexity of this program is O(n+m*s)
 * for(int i = 0; i < size_net; i++)   time complexity is O(n)
 * for(i=0;i<num_tt;i++){
 *     for(j=0;j<num_stop;j++)       time complexity is O(m*s)
 *     dfs_search                     time complexity is O(n+m*s)
*/

#include <stdio.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include <stdbool.h>
#include <time.h>

typedef struct { //站点信息
    char time[5];
    char stop_name[17];
    int transfer_time;
} Stop;
typedef struct EdgeT Edge; // Edge这个类型等同于struct EdgeT这个类型，但是没有定义struct EdgeT，所以接下来定义struct EdgeT
struct EdgeT { // 边的信息
    char time[5];
    int which_route;
    int destination;
    Edge *next;  // next是下一个node的地址
};
typedef struct GraphRep *Graph;
typedef struct GraphRep {
    // array of linked-list(linked-list是Edge*这样的类型)
    Edge **edges; //不知道size所以**
    int nV;
    int nE;
} GraphRep;

typedef struct VisitedT Visited;
struct VisitedT {
    int *visited;
    int* depart_time;
    int* arrival_time;
};

Graph newGraph(int V) {
    assert(V >= 0);
    int i;
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;
    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }
    return g;
}

int find_index(Stop *stops, char *stop_name, int size_net) { //stops是array of stop,传入一个名字，想找到这个名字在哪个index上面
    int i;
    for (i = 0; i < size_net; i++) {
        if (strcmp(stops[i].stop_name, stop_name) == 0) {    //strcmp比较两个string是否相等，相等返回0
            return i;
        }
    }
    return -1;
}

//传入一个时间1345，转换为timestamp
time_t convert_time(char *t) {
    char hour[3];
    char min[3];
    //让hour变成13，让min变成45
    strncpy(hour, t, 2);
    hour[2] = '\0';
    strncpy(min, t + 2, 2);
    min[2] = '\0';
//    //把hour和min转换成int
//    int h = atoi(hour);
//    int m = atoi(min);
//    //把h和m转换成timestamp
//    time_t timestamp = h * 3600 + m * 60;
//    return timestamp;
    struct tm timeStruct; //create一个时间结构体，用来储存时间
    time_t currentTime;
    time(&currentTime);
    struct tm *currentTimeInfo = localtime(&currentTime);//提取当前电脑时间
    timeStruct.tm_year = currentTimeInfo->tm_year;
    timeStruct.tm_mon = currentTimeInfo->tm_mon;
    timeStruct.tm_mday = currentTimeInfo->tm_mday;
    timeStruct.tm_hour = atoi(hour);
    timeStruct.tm_min = atoi(min);
    timeStruct.tm_sec = 0;
    time_t timestamp = mktime(&timeStruct);
    return timestamp;
}

//1405转换成timestamp，160000140500
//1607转换成timestamp，160000160700
time_t time_add(char *time, int min) {
    time_t t = convert_time(time);
    time_t seconds = min * 60;
    struct tm *timeInfo = localtime(&t);
    timeInfo->tm_sec += seconds;
    time_t newT = mktime(timeInfo);
    return newT;

}

//convert_time有更简单的写法，把hour转换成minute，然后相减
int convert_time_minute(char *t) {
    char hour[3];
    char min[3];
    //让hour变成13，让min变成45
    strncpy(hour, t, 2);
    hour[2] = '\0';
    strncpy(min, t + 2, 2);
    min[2] = '\0';
    //把hour转换成minute，minute=60*hour+min
    int h = atoi(hour);
    int m = atoi(min);
    int minute = h * 60 + m;
    return minute;
}

bool check_time(char *time1, char *time2) {
    time_t t1 = convert_time(time1);
    time_t t2 = convert_time(time2);
    if (t1 - t2 <= 0) {
        return true;
    }
    return false;
}

//append本质就是linkedlist加入一个node
Edge *append(Edge *head, char *time, int which_route, int dest) {
    //第一步先要创建一个节点node
    Edge *e = malloc(sizeof(Edge));
    assert(e != NULL);
    e->which_route = which_route;
    e->destination = dest;
    strcpy(e->time, time);
    e->next = NULL;   //已经create完一个node
    //准备加入到linked-list里
    if (head == NULL) { //如果head是空的，那么直接把e加入到head
        head = e;
        return head;
    }
    e->next = head;
    return e;
}
//    //找到第一个比当前时间早的node然后加在前面以达到as late as possible的目的
//    Edge *curr = head,*prev = NULL;
//
//    while (check_time(time, curr->time)) {
//        prev = curr;
//        curr = curr->next;
//        if (curr == NULL) {
//            break;
//        }
//    }
//        prev->next = e;
//        e->next = curr;
//        return head;
//    }
// 不仅要存在一条路径，还要在规定的时间前到达，要判断对应的这条边的时间是否符合要求，
// 比如R有2条边，一条1006，一条1359，但是要求1100到达，那么就要选1006这条边，
// 要先判断这条edge是否符合时间要求
// 对于终点希望不要被考虑在内，
bool dfs_search(Graph g, int from, int to, int *visited, Edge *prev, Stop *stops, char *time_before) {
    if (from == to) {//如果from和to相等，那么就找到了
        return true;
    } else {
        //去当前这个点的邻居,from的邻居在g->edges[from]：linked-list(time,route,dest)里面dest是他的邻居
        Edge *head = g->edges[from];
        while (head != NULL) {
            if (head->destination != -1 && visited[head->destination] == -1 && check_time(head->time, time_before)) {//
                // 排除掉终点，因为终点是-1
                // 没有被visit过,那就去visit他,
                // 并且要判断时间是否符合要求,
                // check_time返回True：if head->time<=time_before,else False

                //要知道下一条要走的路径是否是和上一条路径同一条which_route，不是的话要考虑进去换乘时间
                //假设是不同一条路径if(前一条edge和当前edge属于不同的which_route)
                if (prev != NULL &&
                    prev->which_route != head->which_route) {//知道当前的点，下一个要explore的边是谁，但是不知道前一个边是谁，所以需要保存前一条边
                    int transfer_time = stops[prev->destination].transfer_time;
                    time_t new_time = time_add(head->time, transfer_time);
                    time_t tb = convert_time(time_before);
                    // 判断当前这个点transfer_time+出发时间会不会早于要求时间time_before
                    if (new_time - tb <= 0) {
                        visited[head->destination] = from;
                        if (dfs_search(g, head->destination, to, visited, head, stops, time_before)) {//如果找到了，那么就返回true
                            return true;
                        }
                    }
                } else {//假设是同一条路径if(前一条edge和当前edge属于同一条which_route)
                    visited[head->destination] = from;
                    if (dfs_search(g, head->destination, to, visited, head, stops, time_before)) {//如果找到了，那么就返回true
                        return true;
                    }
                }
            }
            head = head->next;

        }
    }
    return false;
}

//要知道下一条要走的路径是否是和上一条路径同一条which_route，不是的话要考虑进去换乘时间

void print_path(int *visited, Stop *stops, int from, int to) {
    if (to == from) {
        //1406 Central
        //1410 TownHall
        //1430 MilsonsPoint
        printf("%s %s\n",stops[to].time,stops[to].stop_name);
        return;
    }
    print_path(visited, stops, from, visited[to]);
    printf("%s %s\n",stops[to].time,stops[to].stop_name);
}

int main() {
    printf("Size of network: ");
    int size_net;
    scanf("%d", &size_net);
    Graph g = newGraph(size_net); // 创建一个graph，有了size_net个站点
    // 创建array of stops
    Stop *stops = malloc(size_net * sizeof(Stop));
    assert(stops != NULL);
    int i;
    char station_name[17]; // 站点名
    int transfer_time;  // 2,3,4分钟
    for (i = 0; i < size_net; i++) {
        scanf("%s", station_name);
        scanf("%d", &transfer_time); //准备存入array of stops里面，i=0时，（name，transfer_time）
        strcpy(stops[i].stop_name, station_name);
        stops[i].transfer_time = transfer_time;  //已经存好了站点信息
    }
    printf("Number of timetables: ");
    int num_tt; // number of timetables
    scanf("%d", &num_tt);
    int num_stop; // number of stops
    for (i = 0; i < num_tt; i++) {
        printf("Number of stops: ");
        scanf("%d", &num_stop);
        int j;
        char prev[17] = ""; // 此处见下文，上一个站点,前一个stop的name
        char timeonTimetable[5]; // 0945 1020 timetable出发时间
//        char stop_name[17]; // timetable上站点名
        for (j = 0; j < num_stop; j++) {
            //发现得不到目的地，因为数据结构要求（出发时间，路线编号0/1，目的地）
            //edges[出发地].append(上一个出发时间，0，当前站点)
            //这一轮的目的地就是下一轮的出发地，比如读到Ashfield （0945，0，A）加入到edges[H]里面
            //核心：：：：：：读到下一个站点时，才往上一个站点加入一条边
            //为了记住上一个站是谁，需要一个变量prev
//            char timeonTimetable[5]; // 0945 1020 timetable出发时间
            char stop_name[17]; // timetable上站点名
            scanf("%s", stop_name);// 出发地点
            if (strcmp(prev, "") != 0) {//读到第二条边
                // g->edges[prev的index]=append（g->edges[prev的index],timeonTimetable,i,当前stop对应的index）
                // 当读到harrispark，一开始prev是空的
                // 读到ashfield，prev是harrispark，所以edges[H]里面加入一条边（0945，0，A对应的index）
                // 发现需要一个函数来找到prev所记录的stopname所对应的index，还有当前stopname所对应的index
                int prev_index = find_index(stops, prev, size_net);
                int dest_index = find_index(stops, stop_name, size_net);//当前站点
                g->edges[prev_index] = append(g->edges[prev_index], timeonTimetable, i, dest_index);
            }
            scanf("%s", timeonTimetable);//出发时间
            strcpy(stops->time, timeonTimetable);
            strcpy(prev, stop_name); // 把当前站点名字存入prev中
        }
        // 读完一条timetable，要把最后一个站点加入到edges里面
        //比如milsonpoint
        int stop_index = find_index(stops, prev, size_net);
        g->edges[stop_index] = append(g->edges[stop_index], timeonTimetable, i, -1);
    }
    char from[17]; // 用户输入的起点
    char to[17];    //用户输入的终点
    char time_before[5];    //用户输入的预期到达时间，在1040之前到达
    while (1) {
        printf("\n");
        printf("From: ");
        scanf("%s", from);
        if (strcmp(from, "done") == 0) {
            printf("Bye");
            break;
        }
        printf("To: ");
        scanf("%s", to);
        printf("Arrive at or before: ");
        scanf("%s", time_before);
        printf("\n");
        //使用dfs算法找两点之间是否存在路径，
        //所以要找from和to所对应的index
        int from_index = find_index(stops, from, size_net);
        printf("1\n");
        int to_index = find_index(stops, to, size_net);
        printf("2\n");
        //dfs需要一个visited数组，记录哪些点已经被访问过了
        int *visited = malloc(size_net * sizeof(int));


        printf("3\n");
        for (i = 0; i < size_net; i++) {
            visited[i] = -1;
        }
        printf("4\n");
        //设置一个起点，也就是from_index
        visited[from_index] = from_index;
        printf("5\n");
        bool res = dfs_search(g, from_index, to_index, visited, NULL, stops, time_before);//dfs_search返回true或者false
        printf("6\n");
        // 把path存在visited array里面，vistied里面的index对应的是前一个点在哪里
        if (res) {
            print_path(visited, stops, from_index, to_index);
        } else {
            printf("No connection.");
        }
    }
    return 0;
}
