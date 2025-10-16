#include <stdio.h>
#include <klee/klee.h>  // 引入 KLEE 库

void triangle(int n)
{
    int i, k, tmp;

    // 初始化 tmp
    tmp = 0;

    // 外层循环：控制三角形的行数
    for(k = 1; k <= n; k = k + 1)
    {
        // 内层第一个循环：控制空格的数量
        for(i = 1; i <= n - k; i = i + 1)
        {
            // 打印空格
            printf(" ");
        }

        // 内层第二个循环：打印星号，形成三角形的每一行
        for(i = 1; i <= 2 * k - 1; i = i + 1)
        {
            // 打印星号
            printf("*");
        }

        // 换行
        printf("\n");
    }

    return;
}

int main()
{
    int n;

    // 使用 KLEE 插桩，将 n 作为符号值
    klee_make_symbolic(&n, sizeof(n), "n");

    // 由于 KLEE 插桩，n 的值现在是符号值，用户输入将由 KLEE 跟踪
    // 这里不再需要 scanf，因为 n 已经是符号值，KLEE 会自动提供值

    // 调用 triangle 函数打印三角形
    triangle(n);

    return 0;
}
