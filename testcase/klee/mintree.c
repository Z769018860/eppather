#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

#define MAX_VERTICES 10
#define MAX_EDGES 100

int parent[MAX_VERTICES];

// 并查集的查找操作，带路径压缩
int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

// 排序函数，使用快速排序代替冒泡排序
int compare(const void* a, const void* b) {
    return ((int*)a)[2] - ((int*)b)[2]; // 比较边的权重
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

    // 使用快速排序对边按权重排序
    qsort(edges, numEdges, sizeof(edges[0]), compare);

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
    int numVertices, numEdges;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(&numVertices, sizeof(numVertices), "numVertices");
    klee_make_symbolic(&numEdges, sizeof(numEdges), "numEdges");

    // 符号化输入的边数据
    int edgeData[MAX_EDGES][3];
    for (int i = 0; i < numEdges; i++) {
        klee_make_symbolic(&edgeData[i], sizeof(edgeData[i]), "edgeData");
    }

    // 调用 Kruskal 算法
    kruskal(numVertices, numEdges, edgeData);

    return 0;
}
