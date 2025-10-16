#include <stdio.h>
#include <klee/klee.h>  // 引入 KLEE 插桩库

int PartSort(int arr[5], int left, int right) {
    int key;
    int hole;
    
    // KLEE 插桩：将 arr 数组、left 和 right 设为符号输入
    klee_make_symbolic(arr, sizeof(int) * 5, "arr");  // 数组 arr 为符号输入
    klee_make_symbolic(&left, sizeof(left), "left");  // 变量 left 为符号输入
    klee_make_symbolic(&right, sizeof(right), "right");  // 变量 right 为符号输入

    hole = left;
    key = arr[left];
    
    // PartSort 主要是进行一次局部的排序处理
    while (left < right) {
        // 从右向左找到小于key的元素
        while (left < right && arr[right] >= key) {
            right = right - 1;
        }
        arr[hole] = arr[right];
        hole = right;

        // 从左向右找到大于key的元素
        while (left < right && arr[left] <= key) {
            left = left + 1;
        }
        arr[hole] = arr[left];
        hole = left;
    }
    
    // 将key放到最终位置
    arr[hole] = key;
    
    return hole;
}

int main() {
    int arr[5];  // 数组 arr 为输入参数
    int left, right;

    // KLEE 插桩：将 left 和 right 设为符号输入
    klee_make_symbolic(arr, sizeof(int) * 5, "arr");  // 数组 arr 为符号输入
    klee_make_symbolic(&left, sizeof(left), "left");  // 变量 left 为符号输入
    klee_make_symbolic(&right, sizeof(right), "right");  // 变量 right 为符号输入

    // 调用 PartSort 函数
    int result = PartSort(arr, left, right);

    // 打印排序后的数组
    printf("Result index: %d\n", result);
    printf("Sorted array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
