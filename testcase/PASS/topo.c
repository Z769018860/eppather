#include <stdio.h>
#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void topologicalSort( int n) {
    clock_t start, end;
start = clock();
    int inDegree[100] = {0};
    int stack[100], top = -1;
    int i,j,node;

    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            if (graph[j][i]) {
                inDegree[i] = inDegree[i] + 1;
            }
        }
    }

    for (i = 0; i < n; i = i + 1) {
        if (inDegree[i] == 0) {
            top = top + 1;
            stack[top] = i;
        }
    }

    while (top != -1) {
        node = stack[top];
        top = top - 1;

        for (i = 0; i < n; i = i + 1) {
            if (graph[node][i]) {
                inDegree[i] = inDegree[i] - 1;
                if (inDegree[i] == 0) {     
                    top = top + 1;
                    stack[top] = i;
                }
            }
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return;
}

int main() {
    int x,j;
    scanf("%d", &x);
    // 随机构造一个有向无环图（DAG）
    // 仅对 i < j 的节点对考虑边，从而保证不会出现环
// 构造固定的有向无环图（DAG）
for (int i = 0; i < x; i++) {
    for (int j = i + 1; j < x; j++) {
        graph[i][j] = 1;  // i < j 时赋值为1
    }
}

    // 输出构造的邻接矩阵
    printf("\nGraph (Adjacency Matrix):\n");
    for (int i = 0; i < x;i = i + 1) {
        for (int j = 0; j < x; j = j + 1) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 调用拓扑排序函数
    topologicalSort(x);

        // 输出构造的邻接矩阵
        printf("\nGraph after(Adjacency Matrix):\n");
        for (int i = 0; i < x;i = i + 1) {
            for (int j = 0; j < x; j = j + 1) {
                printf("%d ", graph[i][j]);
            }
            printf("\n");
        }
        printf("\n");

    return 0;
}