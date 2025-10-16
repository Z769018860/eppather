#include <stdio.h>

#define MAX_V 100

void topologicalSort(int graph[MAX_V][MAX_V], int n) {
    int inDegree[MAX_V] = {0};
    int stack[MAX_V], top = -1;

    // 计算每个节点的入度
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[j][i]) {
                inDegree[i]++;
            }
        }
    }

    // 入度为0的节点入栈
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            stack[++top] = i;
        }
    }

    // 进行拓扑排序
    while (top != -1) {
        int node = stack[top--];
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (graph[node][i]) {
                if (--inDegree[i] == 0) {
                    stack[++top] = i;
                }
            }
        }
    }

    printf("\n");
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int graph[MAX_V][MAX_V] = {0};

    printf("Enter number of edges: ");
    scanf("%d", &e);
    
    printf("Enter the edges (u v) for directed graph:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    topologicalSort(graph, n);
    return 0;
}
