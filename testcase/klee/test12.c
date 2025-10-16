#include <stdio.h>
#include <klee/klee.h>

void process(int n, int m) {
    int i, j, k;

    while (m) {
        m = m - 1;

        for (i = n; i >= 1; i = i - 1) {
            // 内部循环1
            for (j = i; j < n; j = j + 1)
                k = 0;
            // 内部循环2
            for (j = 1; j <= 2 * i - 1; j = j + 1)
                k = 1;
            k = 2;
        }
    }
}

int main() {
    int n, m;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(&n, sizeof(n), "n");
    klee_make_symbolic(&m, sizeof(m), "m");

    // 调用处理函数
    process(n, m);

    return 0;
}
