#include <stdio.h>
#include <klee/klee.h>  // 引入 KLEE 插桩库

void selectSort(int data[10], int n) {
    int min;
    int i, j;
    int temp;

    // KLEE 插桩：将 data 数组和 n 设为符号输入
    klee_make_symbolic(data, sizeof(int) * 10, "data");  // 数组 data 为符号输入
    klee_make_symbolic(&n, sizeof(n), "n");  // 变量 n 为符号输入

    // 选择排序算法
    for(i = 0; i < n - 1; i = i + 1) {
        min = i;
        for(j = i + 1; j < n; j = j + 1) {
            if(data[j] < data[min]) {
                min = j;
            }
        }

        if(data[i] != data[min]) {
            // 交换 data[i] 和 data[min] 的值
            temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
    }

    // 打印排序后的数组
    for (i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return;
}

int main() {
    int data[10];  // 数组 data 为输入参数
    int n;  // 变量 n 为输入参数

    // KLEE 插桩：将 n 设为符号输入
    klee_make_symbolic(&n, sizeof(n), "n");  // 变量 n 为符号输入

    // KLEE 插桩：将数组 data 设为符号输入
    klee_make_symbolic(data, sizeof(int) * 10, "data");  // 数组 data 为符号输入

    // 调用 selectSort 函数
    selectSort(data, n);

    return 0;
}
