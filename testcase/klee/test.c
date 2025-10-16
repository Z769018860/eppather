#include <stdio.h>
#include <klee/klee.h>

#define M 5

// 处理逻辑的函数
void process(int a, int b, int *c) {
    int sum = 0;

    sum = 3 * M + 4 * M + 5 * M;

    // 对 a 进行处理
    if (a > 0)
        a = a + 1;
    else
        a = a - 1;

    // 循环处理 a
    int i;
    for (i = 0; i < 10; i = i + 1)
        a = a + i;

    // while 循环处理 a 和 b
    while (a > 1) {
        if (b > 0)
            a = a - 1;
        else
            a = a + 2;
    }

    // 赋值 c 和 b
    *c = b = a;

    // 处理 a 的 while 循环
    while (a < 0)
        a = a + 1;
}

// main 函数调用 process 函数
int main() {
    int a, b, c;

    // 使用 KLEE 符号化变量
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&c, sizeof(c), "c");

    // 调用处理逻辑函数
    process(a, b, &c);

    return 0;
}
