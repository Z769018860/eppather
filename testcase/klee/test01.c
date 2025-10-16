#include <stdio.h>
#include <klee/klee.h>

int f(int flag, int x) {
    // 判断 flag 的值，分别执行不同的逻辑
    if (flag > 42) {
        return x + 42;
    } else if (flag == 42) {
        x = x + 1;
    } else {
        int ret = 0;

        // 使用循环对 ret 进行计算
        for (int i = 0; i < x; i = i + 1) {
            ret = ret + i * x;
        }

        return ret;
    }

    return 42 + flag;
}

int main() {
    int flag, x;

    // 使用 KLEE 符号化变量
    klee_make_symbolic(&flag, sizeof(flag), "flag");
    klee_make_symbolic(&x, sizeof(x), "x");

    // 调用 f 函数
    int result = f(flag, x);

    // 打印返回值
    printf("Result: %d\n", result);

    return 0;
}
