#include <stdio.h>
#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int graph[MAXLEN][MAXLEN] = {0};

void topologicalSort( int n) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int inDegree[100];\n");
printf("int stack[100];\n");
printf("int top;\n");
printf("int i;\n");
printf("int j;\n");
printf("int node;\n");
printf("double time_taken;\n");
printf("int graph[1000][1000];\n");


    int inDegree[100] = {0};
    int stack[100], top = -1;
    int i,j,node;

    {
      int __first_iter_flag_0 = 1;
    for (i = 0; i < n; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < n)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_2 = 1;
        for (j = 0; j < n; j = j + 1) {
        if(__first_iter_flag_2) { 
        printf("j = 0;\n"); 
        __first_iter_flag_2 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(j < n)\n");
        path_len = path_len + 1;
        
            if (graph[j][i]) {
            cond_count = cond_count + 1;
            printf("@(graph[j][i])\n");
            path_len = path_len + 1;
            mems = mems + 1;
            
                printf("inDegree[i] = inDegree[i] + 1;\n");
                inDegree[i] = inDegree[i] + 1;
                mems = mems + 2;
                
            }
        printf("j = j + 1;\n");
}
}

    printf("i = i + 1;\n");
}
}


    {
      int __first_iter_flag_1 = 1;
    for (i = 0; i < n; i = i + 1) {
    if(__first_iter_flag_1) { 
    printf("i = 0;\n"); 
    __first_iter_flag_1 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < n)\n");
    path_len = path_len + 1;
    
        if (inDegree[i] == 0) {
        cond_count = cond_count + 1;
        printf("@(inDegree[i] == 0)\n");
        path_len = path_len + 1;
        mems = mems + 1;
        
            printf("top = top + 1;\n");
            top = top + 1;
            
            printf("stack[top] = i;\n");
            stack[top] = i;
            mems = mems + 1;
            
        }
    printf("i = i + 1;\n");
}
}


    while (top != -1) {
    cond_count = cond_count + 1;
    printf("@(top != -1)\n");
    path_len = path_len + 1;
    
        printf("node = stack[top];\n");
        node = stack[top];
        mems = mems + 1;
        
        printf("top = top - 1;\n");
        top = top - 1;
        

        {
          int __first_iter_flag_3 = 1;
        for (i = 0; i < n; i = i + 1) {
        if(__first_iter_flag_3) { 
        printf("i = 0;\n"); 
        __first_iter_flag_3 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < n)\n");
        path_len = path_len + 1;
        
            if (graph[node][i]) {
            cond_count = cond_count + 1;
            printf("@(graph[node][i])\n");
            path_len = path_len + 1;
            mems = mems + 1;
            
                printf("inDegree[i] = inDegree[i] - 1;\n");
                inDegree[i] = inDegree[i] - 1;
                mems = mems + 2;
                
                if (inDegree[i] == 0) {
                cond_count = cond_count + 1;
                printf("@(inDegree[i] == 0)\n");
                path_len = path_len + 1;
                mems = mems + 1;
                     
                    printf("top = top + 1;\n");
                    top = top + 1;
                    
                    printf("stack[top] = i;\n");
                    stack[top] = i;
                    mems = mems + 1;
                    
                }
            }
        printf("i = i + 1;\n");
}
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