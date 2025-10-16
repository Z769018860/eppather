#include <stdio.h>
#include <klee/klee.h>

// 统计数组中满足特定条件的元素
int countSpecialElements(int arr[], int size) {
    int count = 0;

    // 遍历数组
    for (int i = 0; i < size; i++) {
        // 条件1：偶数索引位置的偶数
        if (i % 2 == 0) {
            if (arr[i] % 2 == 0) {
                count++; // 满足条件1
            }
        }

        // 条件2：奇数索引位置的奇数
        if (i % 2 != 0) {
            if (arr[i] % 2 != 0) {
                count++; // 满足条件2
            }
        }

        // 条件3：正数且比前一个数字大
        if (arr[i] > 0) {
            if (i > 0 && arr[i] > arr[i - 1]) {
                count++; // 满足条件3
            }
        }

        // 条件4：负数且比后一个数字小
        if (arr[i] < 0) {
            if (i < size - 1 && arr[i] < arr[i + 1]) {
                count++; // 满足条件4
            }
        }
    }

    return count;
}

int main() {
    int arr[5];
    int size;

    // 将数组和大小声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");
    klee_make_symbolic(&size, sizeof(size), "size");


    countSpecialElements(arr, size);

    return 0;
}
