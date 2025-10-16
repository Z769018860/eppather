#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void floydWarshall(int V, int graph[V][V]) {
    int dist[V][V];

    // 初始化距离矩阵
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    // 执行 Floyd-Warshall 算法
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 输出最短路径矩阵
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int V;
    
    // 用户输入图的顶点数量
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    int graph[V][V];
    
    // 用户输入图的边的权重
    printf("Enter the adjacency matrix (enter 0 for no edge, INF for no connection):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0; // 对角线元素为0，表示顶点到自身的距离为0
            } else {
                printf("Enter the edge weight for (%d, %d): ", i, j);
                int weight;
                scanf("%d", &weight);
                if (weight == -1) {  // -1 表示没有边
                    graph[i][j] = INF;
                } else {
                    graph[i][j] = weight;
                }
            }
        }
    }

    // 调用 Floyd-Warshall 算法
    floydWarshall(V, graph);
    return 0;
}
