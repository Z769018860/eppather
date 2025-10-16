#include <stdio.h>
#include <klee/klee.h>

// 统计数组中的峰谷元素
int countPeaksAndValleys(int arr[], int size) {
    if (size < 3) return 0; // 至少需要3个元素来定义峰谷
    int count = 0;

    for (int i = 1; i < size - 1; i++) {
        // 判断峰
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                count++; // 峰
            }
        }

        // 判断谷
        else if (arr[i] < arr[i - 1]) {
            if (arr[i] < arr[i + 1]) {
                count++; // 谷
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


    countPeaksAndValleys(arr, size);

    return 0;
}
