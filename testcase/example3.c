#include <stdio.h>
#include <klee/klee.h>

// 计算数组的最大乘积子数组
int maxProductSubarray(int arr[], int size) {
    if (size <= 0) return 0;
    int maxProd = arr[0], minProd = arr[0], result = arr[0], temp;

    for (int i = 1; i < size; i++) {
        if (arr[i] < 0) {
            temp = maxProd;
            maxProd = minProd;
            minProd = temp;
        }

        if (arr[i] * maxProd > arr[i]) {
            maxProd = arr[i] * maxProd;
        } else {
            maxProd = arr[i];
        }

        if (arr[i] * minProd < arr[i]) {
            minProd = arr[i] * minProd;
        } else {
            minProd = arr[i];
        }

        if (maxProd > result) {
            result = maxProd;
        }
    }

    return result;
}

int main() {
    int arr[5];
    int size;

    // 将数组和大小声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");
    klee_make_symbolic(&size, sizeof(size), "size");

    maxProductSubarray(arr, size);

    return 0;
}
