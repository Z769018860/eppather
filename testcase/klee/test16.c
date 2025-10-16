#include <stdio.h>
#include <klee/klee.h>

// 核心函数：处理 n, a 的值并进行计算
void process_variables(int n, int a) {
    int i, k;

    if (n > 0) {
        for (i = 0; i < n; i = i + 1) {
            if (a > i) {
                k = 0;
            } else {
                k = 1;
            }
        }
    } else {
        k = 2;
    }
}

int main() {
    int n, a;

    // 使用 KLEE 插桩符号化 n 和 a 变量
    klee_make_symbolic(&n, sizeof(n), "n");
    klee_make_symbolic(&a, sizeof(a), "a");

    // 调用核心处理函数
    process_variables(n, a);

    return 0;
}
