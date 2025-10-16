#include <stdio.h>
#include <klee/klee.h>

// 将核心逻辑提取到一个函数
void process(int a, int b, int c, int d, int e) {
    while (a != b) {
        b = b + 1;  // 增加 b
        c = a % b;  // 计算 a % b

        // 如果 c 为 0，执行以下操作
        if (c == 0) {
            d = d + 1;  // 增加 d
            e = e + b;  // 增加 e
        }
    }
}

int main() {
    int a, b, c, d, e;

    // 使用 KLEE 插桩符号化输入
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&c, sizeof(c), "c");
    klee_make_symbolic(&d, sizeof(d), "d");
    klee_make_symbolic(&e, sizeof(e), "e");

    // 调用处理函数
    process(a, b, c, d, e);

    return 0;
}
