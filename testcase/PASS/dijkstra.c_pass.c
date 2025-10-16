#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void dijkstra(int V,int src) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int V;\n");
printf("int src;\n");
printf("int dist[10];\n");
printf("int sptSet[10];\n");
printf("int min;\n");
printf("int u;\n");
printf("int v;\n");
printf("int count;\n");
printf("double time_taken;\n");
printf("int graph[1000][1000];\n");

    int dist[10], sptSet[10];
    int min, u, v, count;

    {
      int __first_iter_flag_0 = 1;
    for (int i = 0; i < V; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("int i = 0;;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < V)\n");
    path_len = path_len + 1;
    
        printf("dist[i] = 100000;\n");
        dist[i] = 100000;
        mems = mems + 1;
        
        printf("sptSet[i] = 0;\n");
        sptSet[i] = 0;
        mems = mems + 1;
        
    printf("i = i + 1;\n");
}
}

    printf("dist[src] = 0;\n");
    dist[src] = 0;
    mems = mems + 1;
    

    {
      int __first_iter_flag_1 = 1;
    for (count = 0; count < V - 1; count = count + 1) {
    if(__first_iter_flag_1) { 
    printf("count = 0;\n"); 
    __first_iter_flag_1 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(count < V - 1)\n");
    path_len = path_len + 1;
    
        printf("min = 100000;\n");
        min = 100000;
        
        printf("u = -1;\n");
        u = -1;
        

        {
          int __first_iter_flag_2 = 1;
        for (v = 0; v < V; v = v + 1) {
        if(__first_iter_flag_2) { 
        printf("v = 0;\n"); 
        __first_iter_flag_2 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(v < V)\n");
        path_len = path_len + 1;
        
            if (!sptSet[v] && dist[v] <= min) {
            cond_count = cond_count + 1;
            printf("@(!sptSet[v] && dist[v] <= min)\n");
            path_len = path_len + 1;
            mems = mems + 2;
            
                printf("min = dist[v];\n");
                min = dist[v];
                mems = mems + 1;
                
                printf("u = v;\n");
                u = v;
                
            }
        printf("v = v + 1;\n");
}
}


        printf("sptSet[u] = 1;\n");
        sptSet[u] = 1;
        mems = mems + 1;
        

        {
          int __first_iter_flag_3 = 1;
        for (v = 0; v < V; v = v + 1) {
        if(__first_iter_flag_3) { 
        printf("v = 0;\n"); 
        __first_iter_flag_3 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(v < V)\n");
        path_len = path_len + 1;
        
            if (!sptSet[v] && graph[u][v] && dist[u] != 100000 && dist[u] + graph[u][v] < dist[v]) {
            cond_count = cond_count + 1;
            printf("@(!sptSet[v] && graph[u][v] && dist[u] != 100000 && dist[u] + graph[u][v] < dist[v])\n");
            path_len = path_len + 1;
            mems = mems + 6;
            
                printf("dist[v] = dist[u] + graph[u][v];\n");
                dist[v] = dist[u] + graph[u][v];
                mems = mems + 4;
                
            }
        printf("v = v + 1;\n");
}
}

    printf("count = count + 1;\n");
}
}

    printf("end = clock();\n");
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    printf("\nEND\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    printf("Total conditional statements: %d\n", cond_count);
    return;
}

int main() {
    int x,y,j;
    scanf("%d %d", &x,&y);
    // 随机数种子
    // 构造固定图：对于所有 0 ≤ i < j < V，设 graph[i][j] = (j - i) * 2，其余为 0
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            if (i < j) {
                graph[i][j] = (j - i) * 2;
            } else {
                graph[i][j] = 0;
            }
        }
    }
    
    // 输出构造好的邻接矩阵
    printf("\nGraph Adjacency Matrix:\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    
    printf("\nRunning Dijkstra's algorithm from source %d:\n", y);
    dijkstra(x, y);

    return 0;
}