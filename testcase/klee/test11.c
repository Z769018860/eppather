#include <stdio.h>
#include <klee/klee.h>

void change(int g[5][5], int m, int n, int a, int b, int s) {
    int i, j, k = 0;  // k 初始化为 0

    // 修改 g[a][b] 和其相邻元素
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

    // 遍历数组并修改 k 的值
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            k = k + 1;
        }
        k = k + 2;
    }

    // 输出 k 的值
    printf("k = %d\n", k);
    return;
}

int main() {
    int g[5][5]; // 二维数组 g
    int m, n, a, b, s;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(g, sizeof(g), "g");
    klee_make_symbolic(&m, sizeof(m), "m");
    klee_make_symbolic(&n, sizeof(n), "n");
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&s, sizeof(s), "s");

    // 调用 change 函数
    change(g, m, n, a, b, s);

    return 0;
}
