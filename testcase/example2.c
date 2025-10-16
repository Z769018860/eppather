#include <stdio.h>
#include <klee/klee.h>

// 查找三数之和等于target
int threeSum(int arr[], int size, int target) {
    int i, j, k;
    for (i = 0; i < size - 2; i++) {
        for (j = i + 1; j < size - 1; j++) {
            for (k = j + 1; k < size; k++) {
                if (arr[i] + arr[j] + arr[k] == target) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int arr[6];
    int target;
    int size;

    // 将数组和目标值声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");
    klee_make_symbolic(&target, sizeof(target), "target");
    klee_make_symbolic(&size, sizeof(size), "size");

    threeSum(arr, size, target);

    return 0;
}
