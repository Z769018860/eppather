#include <stdio.h>
#include <klee/klee.h>

// 核心函数：计算从 2 到 n 的阶乘积
void calculate_product(int n) {
    int i = 2;
    int product = 1;

    // 计算阶乘的乘积
    while (i <= n) {
        product = i * product;
        i = i + 1;
    }

    // 打印最终的结果
    printf("Product: %d\n", product);
}

int main() {
    int n;

    // 使用 KLEE 插桩符号化 n 变量
    klee_make_symbolic(&n, sizeof(n), "n");

    // 调用核心函数
    calculate_product(n);

    return 0;
}
