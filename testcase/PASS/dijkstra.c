#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void dijkstra(int V,int src) {
clock_t start, end;
start = clock();
    int dist[10], sptSet[10];
    int min, u, v, count;

    for (int i = 0; i < V; i = i + 1) {
        dist[i] = 100000;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (count = 0; count < V - 1; count = count + 1) {
        min = 100000;
        u = -1;

        for (v = 0; v < V; v = v + 1) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        sptSet[u] = 1;

        for (v = 0; v < V; v = v + 1) {
            if (!sptSet[v] && graph[u][v] && dist[u] != 100000 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return;
}

int main() {
    int x,y,j;
    scanf("%d %d", &x,&y);
    // 随机数种子
    // 构造固定图：对于所有 0 ≤ i < j < V，设 graph[i][j] = (j - i) * 2，其余为 0
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            if (i < j) {
                graph[i][j] = (j - i) * 2;
            } else {
                graph[i][j] = 0;
            }
        }
    }
    
    // 输出构造好的邻接矩阵
    printf("\nGraph Adjacency Matrix:\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    
    printf("\nRunning Dijkstra's algorithm from source %d:\n", y);
    dijkstra(x, y);

    return 0;
}