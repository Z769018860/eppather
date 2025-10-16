#include <stdio.h>

#define MAX_VERTICES 10
#define MAX_EDGES 100

int parent[MAX_VERTICES];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void kruskal(int numVertices, int numEdges, int edgeData[][3]) {
    int edges[MAX_EDGES][3];
    int mstWeight = 0;

    // 初始化父节点
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    // 将边数据复制到 edges 数组
    for (int i = 0; i < numEdges; i++) {
        edges[i][0] = edgeData[i][0];
        edges[i][1] = edgeData[i][1];
        edges[i][2] = edgeData[i][2];
    }

    // 排序边（冒泡排序）
    for (int i = 0; i < numEdges - 1; i++) {
        for (int j = 0; j < numEdges - i - 1; j++) {
            if (edges[j][2] > edges[j + 1][2]) {
                int temp_u = edges[j][0];
                int temp_v = edges[j][1];
                int temp_weight = edges[j][2];
                edges[j][0] = edges[j + 1][0];
                edges[j][1] = edges[j + 1][1];
                edges[j][2] = edges[j + 1][2];
                edges[j + 1][0] = temp_u;
                edges[j + 1][1] = temp_v;
                edges[j + 1][2] = temp_weight;
            }
        }
    }

    // Kruskal 算法核心
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];

        if (find(u) != find(v)) {
            printf("Edge (%d, %d) with weight %d included in MST\n", u, v, weight);
            mstWeight += weight;
            parent[find(u)] = find(v);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
}

int main() {
    int edgeData[5][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskal(4, 5, edgeData);
    return 0;
}
