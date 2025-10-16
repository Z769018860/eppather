#include <stdio.h>
#include <klee/klee.h>  // 引入 KLEE 插桩库

void reserve1(int a[5], int n) {
    int m;
    int i = 0;
    int temp;

    // KLEE 插桩：将 n 设为符号变量
    klee_make_symbolic(&n, sizeof(n), "n");  // 变量 n 为符号变量
    m = (n + 1) / 2;  // 计算 m

    // KLEE 插桩：将数组 a 设为符号输入
    klee_make_symbolic(a, sizeof(int) * 5, "a");  // 数组 a 为符号数组

    // 遍历数组并交换
    for (i = 0; i < m; i++) {
        int j = n - 1 - i;
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    
    // 打印数组内容以便验证
    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[5];  // 数组 a 作为输入参数
    int b;  // 变量 b 用作输入参数

    // KLEE 插桩：将 b 设为符号变量
    klee_make_symbolic(&b, sizeof(b), "b");  // 变量 b 为符号变量
    
    // KLEE 插桩：将数组 a 设为符号输入
    klee_make_symbolic(a, sizeof(int) * 5, "a");  // 数组 a 为符号数组

    // 调用 reserve1 函数，传递 a 和 b
    reserve1(a, b);

    return 0;
}
