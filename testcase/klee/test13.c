#include <stdio.h>
#include <klee/klee.h>

void process(int a, int b, int c) {
    // 主 while 循环条件：a 非零且 a < 100
    while (a && a < 100) {
        a = a + 1;
        b = 1;

        // 内部 while 循环：当 c 非零时执行
        while (c) {
            b = b + 1;
            c = a % b;  // 更新 c 的值
        }

        // 条件判断：如果 a == b，则不做任何操作
        if (a == b) {
            // Do nothing
        }

        c = 1;  // 将 c 重新设置为 1
    }
}

int main() {
    int a, b, c;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&c, sizeof(c), "c");

    // 调用处理函数
    process(a, b, c);

    return 0;
}
