#include <stdio.h>
#include <klee/klee.h>

void sort(int n, int a[]) {
    int cur, j, low_ind, temp;

    // 使用选择排序算法
    for (cur = 0; cur < n - 1; cur = cur + 1) {
        low_ind = cur;
        for (j = cur + 1; j < n; j = j + 1) {
            if (a[j] < a[low_ind]) {
                low_ind = j;
            }
        }

        // 交换 a[cur] 和 a[low_ind]
        temp = a[cur];
        a[cur] = a[low_ind];
        a[low_ind] = temp;
    }

    return;
}

int main() {
    int n;

    // 使用 KLEE 插桩，符号化 n
    klee_make_symbolic(&n, sizeof(n), "n");

    // 确保 n 在合理范围内
    if (n <= 0 || n > 100) {
        return 0; // 如果 n 不合法，直接返回
    }

    int a[n];

    // 使用 KLEE 插桩符号化数组 a
    klee_make_symbolic(a, sizeof(a), "a");

    // 调用排序函数
    sort(n, a);

    // 打印排序后的数组
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
