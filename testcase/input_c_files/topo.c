#include <stdio.h>
#include <klee/klee.h>

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

    // 使用 KLEE 插桩，符号化节点数 n 和边数 e
    klee_make_symbolic(&n, sizeof(n), "n");
    klee_make_symbolic(&e, sizeof(e), "e");

    // 确保节点数和边数在合理范围内
    if (n <= 0 || e < 0 || e > n * (n - 1) / 2) {
        return 0;  // 不合法输入直接返回
    }

    int graph[MAX_V][MAX_V] = {0};

    // 使用 KLEE 插桩符号化图的边
    for (int i = 0; i < e; i++) {
        int u, v;
        klee_make_symbolic(&u, sizeof(u), "u");
        klee_make_symbolic(&v, sizeof(v), "v");

        // 确保 u 和 v 是有效的
        if (u >= 0 && u < n && v >= 0 && v < n) {
            graph[u][v] = 1;
        }
    }

    // 调用拓扑排序函数
    topologicalSort(graph, n);
    return 0;
}
