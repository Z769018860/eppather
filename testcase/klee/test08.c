#include <stdio.h>
#include <klee/klee.h>

void insert(int data, int len) {
    int a[5];  // 假设数组大小为5
    int k = 0;
    int i;

    // 使用 KLEE 插桩来符号化输入
    klee_make_symbolic(a, sizeof(a), "a");

    // 查找插入位置
    while (k < len && a[k] < data) {
        k = k + 1;
    }

    // 右移元素
    for (i = len; i > k; i = i - 1) {
        a[i] = a[i - 1];
    }

    // 插入数据
    if (k < 5) {
        a[k] = data;
    }

    // 打印结果
    printf("Array after insertion: ");
    for (i = 0; i < len + 1 && i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return;
}

int main() {
    int data, len;

    // 使用 KLEE 插桩来符号化输入
    klee_make_symbolic(&data, sizeof(data), "data");
    klee_make_symbolic(&len, sizeof(len), "len");

    // 调用插入函数
    insert(data, len);

    return 0;
}
