#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void floydWarshall(int V) {
clock_t start, end;
start = clock();
    int dist[MAXLEN][MAXLEN];
    int i, j, k;

    for (i = 0; i < V; i = i + 1) {
        for (j = 0; j < V; j = j + 1) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = 2147483647;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    for (k = 0; k < V; k = k + 1) {
        for (i = 0; i < V; i = i + 1) {
            for (j = 0; j < V; j = j + 1) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
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
    int x,i,j;
    scanf("%d", &x);
    // 构造固定的图：
    // 对于所有 0 ≤ i, j < V，如果 i < j，则设 graph[i][j] = i + j；
    // 其余（包括 i == j 或 i > j）保持为 0，表示没有边。
    for (i = 0; i < x; i = i + 1) {
        for (j = 0; j < x; j = j + 1) {
            if (i < j)
                graph[i][j] = i + j;
            else
                graph[i][j] = 0;
        }
    }
    
    // 输出构造好的邻接矩阵
    printf("\n固定图的邻接矩阵:\n");
    for (i = 0; i < x; i = i + 1) {
        for (j = 0; j < x; j = j + 1) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    
    // 调用 Floyd–Warshall 算法
    floydWarshall(x);
    return 0;
}