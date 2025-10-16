#include <stdio.h>
#include <klee/klee.h>

int fib(int k, int m) {
    int i, j, sum;
    int f[10];

    // 边界条件
    if (m <= k - 2) return 0;
    if (m == k - 2) return 1;

    // 初始化前 k-1 个元素为 0，第 k 个元素为 1
    for (i = 0; i <= k - 2; i++)
        f[i] = 0;
    f[k - 1] = 1;

    // 计算从第 k 到第 m 个元素
    for (i = k; i <= m; i++) {
        sum = 0;
        for (j = i - k; j < i; j++) {
            sum += f[j];
        }
        f[i] = sum;
    }

    return f[m];
}

int main() {
    int k, m;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(&k, sizeof(k), "k");
    klee_make_symbolic(&m, sizeof(m), "m");

    // 调用斐波那契函数
    int result = fib(k, m);

    // 输出结果
    printf("fib(%d, %d) = %d\n", k, m, result);
    return 0;
}
