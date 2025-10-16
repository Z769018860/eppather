#include <stdio.h>
#include <limits.h>
#include <klee/klee.h>

#define INF INT_MAX

void dijkstra(int V, int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];  // Shortest Path Tree set

    // Initialize distances and sptSet
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int min = INF, u;

        // Find the vertex with the minimum distance
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        // Mark u as processed
        sptSet[u] = 1;

        // Update the distance of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

int main() {
    int V;

    // 使用 klee 符号化顶点数量
    klee_make_symbolic(&V, sizeof(V), "V");
    //klee_assume(V > 0 && V <= 100);  // 假设顶点数量合理

    int graph[V][V];

    // 使用 klee 符号化图的邻接矩阵
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0;  // 对角线元素设置为0，表示顶点到自身的距离为0
            } else {
                int weight;
                klee_make_symbolic(&weight, sizeof(weight), "weight");
                //klee_assume(weight >= 0);  // 假设边权重非负
                if (weight == 0) {
                    graph[i][j] = INF;  // 如果没有边连接，设置为INF
                } else {
                    graph[i][j] = weight;  // 如果有边，设置为权重
                }
            }
        }
    }

    int src;
    // 使用 klee 符号化源点
    klee_make_symbolic(&src, sizeof(src), "src");
    //klee_assume(src >= 0 && src < V);  // 假设源点合法

    // 调用 Dijkstra 算法
    dijkstra(V, graph, src);

    return 0;
}
