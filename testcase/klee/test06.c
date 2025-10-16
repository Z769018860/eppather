#include <stdio.h>
#include <klee/klee.h>

void bubble(int n, int a[]) {
    int i, j, lx;
    i = n - 1;
    
    // 冒泡排序
    while (i > 0) {
        lx = 0;
        j = 0;
        while (j < i) {
            if (a[j + 1] < a[j]) {
                // 交换 a[j+1] 和 a[j]
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                lx = j;
            }
            j = j + 1;
        }
        i = lx;
    }
}

int main() {
    int n;

    // 使用 KLEE 插桩，符号化 n
    klee_make_symbolic(&n, sizeof(n), "n");

    // 确保 n 在合理范围内
    if (n <= 0 || n > 5) {
        return 0; // 如果 n 不合法，直接返回
    }

    int a[n];

    // 使用 KLEE 插桩符号化数组 a
    klee_make_symbolic(a, sizeof(a), "a");

    // 调用冒泡排序函数
    bubble(n, a);

    // 打印排序后的数组
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
