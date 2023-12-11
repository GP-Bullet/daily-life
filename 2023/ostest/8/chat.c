#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 101
#define MAX_TIME_LENGTH 6
#define MAX_NUM_STATIONS 10001

typedef struct Station {
    int id;
    char name[MAX_NAME_LENGTH];
} Station;

typedef struct Timetable {
    Station *to;
    char departure[MAX_TIME_LENGTH];
    char arrival[MAX_TIME_LENGTH];
    struct Timetable *next;
} Timetable;

typedef struct Connection {
    int num_stations;
    Station **stations;
    Timetable **timetables;
    struct Connection *next;
} Connection;

// 将一个火车站添加到站点列表中
void add_station(int id, char *name, Station **station_list) {
    Station *station = malloc(sizeof(Station));
    station->id = id;
    strcpy(station->name, name);
    station_list[id] = station;
}

// 构建火车网络中的邻接表
Timetable **build_adj_list(Station **station_list, int num_stations) {
    Timetable **adj_list = calloc(num_stations, sizeof(Timetable *));
    int num_timetables;
    scanf("%d", &num_timetables);
    for (int i = 0; i < num_timetables; i++) {
        int num_stops;
        scanf("%d", &num_stops);
        Station *prev_station = NULL;
        for (int j = 0; j < num_stops; j++) {
            int id;
            char departure[MAX_TIME_LENGTH];
            char arrival[MAX_TIME_LENGTH];
            scanf("%d%s%s", &id, departure, arrival);
            Station *station = station_list[id];
            if (prev_station != NULL) {
                Timetable *timetable = malloc(sizeof(Timetable));
                timetable->to = station;
                strcpy(timetable->departure, departure);
                strcpy(timetable->arrival, arrival);
                timetable->next = adj_list[prev_station->id];
                adj_list[prev_station->id] = timetable;
            }
            prev_station = station;
        }
    }
    return adj_list;
}

// 向火车网络中添加一个连接
void append_connection(Connection *connection, Connection **connection_list) {
    connection->next = *connection_list;
    *connection_list = connection;
}

// 在火车网络中查找指定的火车站
Station *find_station(int id, Connection *connection_list) {
    while (connection_list != NULL) {
        for (int i = 0; i < connection_list->num_stations; i++) {
            if (connection_list->stations[i]->id == id) {
                return connection_list->stations[i];
            }
        }
        connection_list = connection_list->next;
    }
    return NULL;
}

// 打印火车站的名称
void print_station_name(char *name) {
    printf("%s ", name);
}

// 判断出发时间是否在到达时间之前
int is_valid_departure_time(char *departure_time, char *arrival_time) {
    return strcmp(departure_time, arrival_time) <= 0;
}

// 在火车网络中查找从起始站到终点站的路径
int dfs_find_path(int from_id, int to_id, char *arrival_time, int *visited, Connection *conn, int depth) {
    visited[from_id] = 1;
    if (from_id == to_id) {
        return 1;
    }
    Timetable *timetable = conn->timetables[from_id];
    while (timetable != NULL) {
        if (!visited[timetable->to->id]) {
            if (is_valid_departure_time(timetable->departure, arrival_time)) {
                int found = dfs_find_path(timetable->to->id, to_id, timetable->arrival, visited, conn, depth + 1);
                if (found) {
                    print_station_name(timetable->to->name);
                    printf("%s\n", timetable->departure);
                    return 1;
                }
            }
        }
        timetable = timetable->next;
    }
    return 0;
}

// 释放火车网络及其相关的内存
void free_connections(Connection *connection_list) {
    while (connection_list != NULL) {
        Connection *connection = connection_list;
        connection_list = connection_list->next;
        for (int i = 0; i < connection->num_stations; i++) {free(connection->stations[i]);
}
for (int i = 0; i < connection->num_stations; i++) {
Timetable *timetable = connection->timetables[i];
while (timetable != NULL) {
Timetable *next_timetable = timetable->next;
free(timetable);
timetable = next_timetable;
}
}
free(connection->stations);
free(connection->timetables);
free(connection);
}
}

int main() {
int num_stations;
scanf("%d", &num_stations);
Station **station_list = calloc(num_stations, sizeof(Station *));
for (int i = 0; i < num_stations; i++) {
int id;
char name[MAX_NAME_LENGTH];
scanf("%d%s", &id, name);
add_station(id, name, station_list);
}
Connection *connection_list = NULL;
int num_connections;
scanf("%d", &num_connections);
for (int i = 0; i < num_connections; i++) {
int num_stations_in_connection;
scanf("%d", &num_stations_in_connection);
Station **stations = malloc(num_stations_in_connection * sizeof(Station *));
for (int j = 0; j < num_stations_in_connection; j++) {
int id;
scanf("%d", &id);
stations[j] = find_station(id, connection_list);
if (stations[j] == NULL) {
stations[j] = station_list[id];
}
}
Timetable **timetables = build_adj_list(stations, num_stations_in_connection);
Connection *connection = malloc(sizeof(Connection));
connection->num_stations = num_stations_in_connection;
connection->stations = stations;
connection->timetables = timetables;
append_connection(connection, &connection_list);
}
int num_queries;
scanf("%d", &num_queries);
for (int i = 0; i < num_queries; i++) {
int from_id, to_id;
char departure_time[MAX_TIME_LENGTH];
scanf("%d%d%s", &from_id, &to_id, departure_time);
int *visited = calloc(num_stations, sizeof(int));
Station *from_station = station_list[from_id];
Station *to_station = station_list[to_id];
print_station_name(from_station->name);
printf("%s\n", departure_time);
int found = 0;
Connection *conn = connection_list;
while (conn != NULL && !found) {
if (conn->num_stations > 0 && conn->stations[0]->id == from_id) {
found = dfs_find_path(0, conn->num_stations - 1, departure_time, visited, conn, 0);
}
conn = conn->next;
}
if (!found) {
printf("No connection found\n");
}
free(visited);
}
free_connections(connection_list);
for (int i = 0; i < num_stations; i++) {
free(station_list[i]);
}
free(station_list);
return 0;
}