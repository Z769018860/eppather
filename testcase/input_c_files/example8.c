#include <stdio.h>
#include <klee/klee.h>

// 检查数组中的递增和递减特殊模式
int countAlternatingPeaksAndValleys(int arr[], int size) {
    if (size < 3) return 0; // 至少需要3个元素才能检测模式
    int count = 0;
    int isPeak = 0; // 记录当前是否处于峰的状态

    for (int i = 1; i < size - 1; i++) {
        // 条件1：检测“峰”——前大后小
        if (arr[i] > 0) {
            if (arr[i] > arr[i - 1]) {
                if (arr[i] > arr[i + 1]) {
                    if (!isPeak) {
                        count++; // 找到峰
                        isPeak = 1;
                    }
                }
            }

            // 条件2：检测“谷”——前小后大
            if (arr[i] < arr[i - 1]) {
                if (arr[i] < arr[i + 1]) {
                    if (isPeak) {
                        count++; // 找到谷
                        isPeak = 0;
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


    countAlternatingPeaksAndValleys(arr, size);

    return 0;
}
