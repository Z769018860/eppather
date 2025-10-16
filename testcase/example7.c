#include <stdio.h>
#include <klee/klee.h>

// 查找数组中满足特定条件的元素
int countSpecialElementsAndOperate(int arr[], int size) {
    int count = 0;

    // 遍历数组
    for (int i = 0; i < size; i++) {
        // 条件1：偶数且大于前一个元素
        if (arr[i] % 2 == 0) {
            if (i > 0 && arr[i] > arr[i - 1]) {
                count++; // 满足条件1
            }
        }

        // 条件2：奇数且小于后一个元素
        if (arr[i] % 2 != 0) {
            if (i < size - 1 && arr[i] < arr[i + 1]) {
                count++; // 满足条件2
            }
        }

        // 条件3：当前元素与前后相邻元素的和为零
        if (i > 0 && i < size - 1) {
            if (arr[i] + arr[i - 1] + arr[i + 1] == 0) {
                count++; // 满足条件3
            }
        }

        // 条件4：当前元素是负数且位于奇数索引位置
        if (arr[i] < 0) {
            if (i % 2 != 0) {
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


    countSpecialElementsAndOperate(arr, size);

    return 0;
}
