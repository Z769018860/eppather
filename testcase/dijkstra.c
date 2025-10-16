#include <stdio.h>
#include <limits.h>

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

    // 用户输入顶点数量
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    int graph[V][V];

    // 用户输入图的邻接矩阵
    printf("Enter the adjacency matrix (enter 0 for no edge, positive numbers for edge weights):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0;  // 对角线元素设置为0，表示顶点到自身的距离为0
            } else {
                printf("Enter the edge weight for (%d, %d): ", i, j);
                int weight;
                scanf("%d", &weight);
                if (weight == 0) {
                    graph[i][j] = INF;  // 如果没有边连接，设置为INF
                } else {
                    graph[i][j] = weight;  // 如果有边，设置为权重
                }
            }
        }
    }

    int src;
    // 用户输入源点
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // 调用 Dijkstra 算法
    dijkstra(V, graph, src);

    return 0;
}
