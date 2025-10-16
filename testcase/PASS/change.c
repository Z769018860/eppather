#include <stdio.h>
#include <time.h>

#define MAXLEN 1000
int g[MAXLEN][MAXLEN] = {0};

void change(int m, int n, int a, int b, int s) {
    clock_t start, end;
    start = clock();
    int i, j, k = 0;

    g[a][b] = s;
    if (a - 1 >= 0) {
        g[a - 1][b] = s;
        if (b - 1 >= 0)
            g[a - 1][b - 1] = s;
    }
    if (b - 1 >= 0)
        g[a][b - 1] = s;
    if (a + 1 < m) {
        g[a + 1][b] = s;
        if (b + 1 < n)
            g[a + 1][b + 1] = s;
    }
    if (b + 1 < n)
        g[a][b + 1] = s;

    for (i = 0; i < m; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            k = k + 1;
        }
        k = k + 2;
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
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