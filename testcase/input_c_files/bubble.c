#include <stdio.h>
#include <klee/klee.h>

// 函数：冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // 最后 i 个元素已经是排好序的
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 主函数
int main() {
    int n;

    // 使用 klee 符号化数组大小
    klee_make_symbolic(&n, sizeof(n), "n");
    //klee_assume(n > 0 && n <= 100);  // 假设数组大小合理，最多为 100

    int arr[n];

    // 使用 klee 符号化数组元素
    klee_make_symbolic(arr, sizeof(arr), "arr");

    // 调用冒泡排序算法
    bubbleSort(arr, n);

    // 输出排序后的数组
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
