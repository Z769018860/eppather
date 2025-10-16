#include <stdio.h>
#include <klee/klee.h>  // KLEE 插桩头文件

int binary_search(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;  // 找到目标，返回其索引
        }
        else if (arr[mid] < target) {
            left = mid + 1;  // 在右半部分查找
        }
        else {
            right = mid - 1;  // 在左半部分查找
        }
    }

    return -1;  // 未找到目标
}

int main() {
    int n, target;

    // 使用 klee_make_symbolic 来符号化输入
    klee_make_symbolic(&n, sizeof(n), "n");
    //klee_assume(n > 0 && n <= 1000);  // 假设数组大小是合理的

    int arr[n];

    // 使用 klee_make_symbolic 来符号化数组的元素
    for (int i = 0; i < n; i++) {
        klee_make_symbolic(&arr[i], sizeof(arr[i]), "arr[i]");
        //klee_assume(arr[i] >= -1000 && arr[i] <= 1000);  // 假设数组元素的范围
    }

    // 使用 klee_make_symbolic 来符号化目标值
    klee_make_symbolic(&target, sizeof(target), "target");
    //klee_assume(target >= -1000 && target <= 1000);  // 假设目标值的范围

    // 调用二分查找函数
    int result = binary_search(arr, n, target);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
