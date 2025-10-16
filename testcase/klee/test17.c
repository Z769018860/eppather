#include <stdio.h>
#include <klee/klee.h>

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (high + low) / 2;

        if (x > v[mid]) {
            low = mid + 1;
        } else if (x < v[mid]) {
            high = mid - 1;
        } else {
            return mid;  // 找到目标值，返回索引
        }
    }

    return -1;  // 未找到目标值
}

int main() {
    int x, n;

    // 符号化 x 和 n 变量
    klee_make_symbolic(&x, sizeof(x), "x");
    klee_make_symbolic(&n, sizeof(n), "n");

    // 符号化数组 v，长度为 5
    int v[5];
    klee_make_symbolic(v, sizeof(v), "v");

    // 调用二分查找函数
    int result = binsearch(x, v, n);

    // 输出结果
    printf("Result: %d\n", result);

    return 0;
}
