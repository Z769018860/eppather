#include <stdio.h>
#include <klee/klee.h>

// 检测数组中奇数和偶数索引上的特殊关系
int countOddEvenIndexRelations(int arr[], int size) {
    if (size < 2) return 0; // 至少需要2个元素才能检测
    int count = 0;

    for (int i = 1; i < size - 1; i++) {
        // 条件1：奇数索引位置的偶数，且比前一个元素小
        if (i % 2 != 0) {
            if (arr[i] % 2 == 0) {
                if (arr[i] < arr[i - 1]) {
                    if (arr[i] != 0) {
                        count++; // 满足条件1
                    }
                }
            }
        }

        // 条件2：偶数索引位置的奇数，且比后一个元素大
        if (i % 2 == 0) {
            if (arr[i] % 2 != 0) {
                if (arr[i] > arr[i + 1]) {
                    if (arr[i] != 0) {
                        count++; // 满足条件2
                    }
                }
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


    countOddEvenIndexRelations(arr, size);

    return 0;
}
