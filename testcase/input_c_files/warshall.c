#include <stdio.h>
#include <limits.h>
#include <klee/klee.h>

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
    
    // 使用 KLEE 插桩符号化顶点数量
    klee_make_symbolic(&V, sizeof(V), "V");

    if (V <= 0 || V > 100) {
        return 0; // 确保V在合理范围内
    }

    int graph[V][V];
    
    // 使用 KLEE 插桩符号化图的边权
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0; // 对角线元素为0，表示顶点到自身的距离为0
            } else {
                int weight;
                klee_make_symbolic(&weight, sizeof(weight), "weight"); // 符号化每个边的权重
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
