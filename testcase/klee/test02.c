#include <stdio.h>
#include <klee/klee.h>

// 单元函数：执行循环和条件判断的逻辑
int process_logic(int a, int b, int c, int g, int e) {

    // 使用 while 循环直到 a == b + 1
    while (a != b + 1) {
        // 条件判断，修改 e 的值
        if (g == c) {
            e = e + 1;  // 如果 g 等于 c，e 自增
        } else {
            e = e - 1;  // 否则 e 自减
        }

        // a 自增
        a = a + 1;
    }

    // 输出最终 e 的值
    printf("Final value of e: %d\n", e);

    // 返回修改后的 e
    return e;
}

int main() {
    // 定义变量
    int a, b, c, g, e;

    // 符号化输入值
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&c, sizeof(c), "c");
    klee_make_symbolic(&g, sizeof(g), "g");
    klee_make_symbolic(&e, sizeof(e), "e");

    // 调用 process_logic 函数，并获取返回值
    e = process_logic(a, b, c, g, e);

    return 0;
}
