#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void floydWarshall(int V) {
int path_len = 0;
int mems = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int V;\n");
printf("int dist[1000][1000];\n");
printf("int i;\n");
printf("int j;\n");
printf("int k;\n");
printf("int graph[1000][1000];\n");

    int dist[MAXLEN][MAXLEN];
    int i, j, k;

    {
      int __first_iter_flag_0 = 1;
    for (i = 0; i < V; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    printf("@(i < V)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_2 = 1;
        for (j = 0; j < V; j = j + 1) {
        if(__first_iter_flag_2) { 
        printf("j = 0;\n"); 
        __first_iter_flag_2 = 0; 
        }
        printf("@(j < V)\n");
        path_len = path_len + 1;
        
            if (graph[i][j] == 0 && i != j) {
            printf("@(graph[i][j] == 0 && i != j)\n");
            path_len = path_len + 1;
            
                printf("dist[i][j] = 2147483647;\n");
                dist[i][j] = 2147483647;
                mems = mems + 2;
                
            } else {
            printf("@(!(graph[i][j] == 0 && i != j))\n");
            path_len = path_len + 1;
            
                printf("dist[i][j] = graph[i][j];\n");
                dist[i][j] = graph[i][j];
                mems = mems + 4;
                
            }
        printf("j = j + 1;\n");
}
}

    printf("i = i + 1;\n");
}
}


    {
      int __first_iter_flag_1 = 1;
    for (k = 0; k < V; k = k + 1) {
    if(__first_iter_flag_1) { 
    printf("k = 0;\n"); 
    __first_iter_flag_1 = 0; 
    }
    printf("@(k < V)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_3 = 1;
        for (i = 0; i < V; i = i + 1) {
        if(__first_iter_flag_3) { 
        printf("i = 0;\n"); 
        __first_iter_flag_3 = 0; 
        }
        printf("@(i < V)\n");
        path_len = path_len + 1;
        
            {
              int __first_iter_flag_4 = 1;
            for (j = 0; j < V; j = j + 1) {
            if(__first_iter_flag_4) { 
            printf("j = 0;\n"); 
            __first_iter_flag_4 = 0; 
            }
            printf("@(j < V)\n");
            path_len = path_len + 1;
            
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                printf("@(dist[i][j] > dist[i][k] + dist[k][j])\n");
                path_len = path_len + 1;
                
                    printf("dist[i][j] = dist[i][k] + dist[k][j];\n");
                    dist[i][j] = dist[i][k] + dist[k][j];
                    mems = mems + 6;
                    
                }
            printf("j = j + 1;\n");
}
}

        printf("i = i + 1;\n");
}
}

    printf("k = k + 1;\n");
}
}

    printf("\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
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