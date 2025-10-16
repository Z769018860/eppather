#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int g[MAXLEN][MAXLEN] = {0};

void change(int m, int n, int a, int b, int s) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int m;\n");
printf("int n;\n");
printf("int a;\n");
printf("int b;\n");
printf("int s;\n");
printf("int i;\n");
printf("int j;\n");
printf("int k;\n");
printf("double time_taken;\n");
printf("int g[1000][1000];\n");
    
    int i, j, k = 0;

    printf("g[a][b] = s;\n");
    g[a][b] = s;
    mems = mems + 2;
    
    if (a - 1 >= 0) {
    cond_count = cond_count + 1;
    printf("@(a - 1 >= 0)\n");
    path_len = path_len + 1;
    
        printf("g[a - 1][b] = s;\n");
        g[a - 1][b] = s;
        mems = mems + 2;
        
        if (b - 1 >= 0)
            {
printf("g[a - 1][b - 1] = s;\n");
            cond_count = cond_count + 1;
            printf("@(b - 1 >= 0)\n");
            path_len = path_len + 1;
            g[a - 1][b - 1] = s;
}
            mems = mems + 2;
            
    }
    if (b - 1 >= 0)
        {
printf("g[a][b - 1] = s;\n");
        cond_count = cond_count + 1;
        printf("@(b - 1 >= 0)\n");
        path_len = path_len + 1;
        g[a][b - 1] = s;
}
        mems = mems + 2;
        
    if (a + 1 < m) {
    cond_count = cond_count + 1;
    printf("@(a + 1 < m)\n");
    path_len = path_len + 1;
    
        printf("g[a + 1][b] = s;\n");
        g[a + 1][b] = s;
        mems = mems + 2;
        
        if (b + 1 < n)
            {
printf("g[a + 1][b + 1] = s;\n");
            cond_count = cond_count + 1;
            printf("@(b + 1 < n)\n");
            path_len = path_len + 1;
            g[a + 1][b + 1] = s;
}
            mems = mems + 2;
            
    }
    if (b + 1 < n)
        {
printf("g[a][b + 1] = s;\n");
        cond_count = cond_count + 1;
        printf("@(b + 1 < n)\n");
        path_len = path_len + 1;
        g[a][b + 1] = s;
}
        mems = mems + 2;
        

    {
      int __first_iter_flag_0 = 1;
    for (i = 0; i < m; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < m)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_1 = 1;
        for (j = 0; j < n; j = j + 1) {
        if(__first_iter_flag_1) { 
        printf("j = 0;\n"); 
        __first_iter_flag_1 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(j < n)\n");
        path_len = path_len + 1;
        
            printf("k = k + 1;\n");
            k = k + 1;
            
        printf("j = j + 1;\n");
}
}

        printf("k = k + 2;\n");
        k = k + 2;
        
    printf("i = i + 1;\n");
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
    int m,n,a,b,s,j,i;
    scanf("%d %d %d %d %d", &m,&n,&a,&b,&s);
    
    // 调用 change 函数修改矩阵中指定位置及其邻域
    change(m, n, a, b, s);

    // 输出修改后的矩阵
    printf("\n修改后的矩阵 (前 %d 行 %d 列):\n", m, n);
    for (i = 0; i < m; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }

    return 0;
}