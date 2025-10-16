#include <stdio.h>

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

    // 用户输入数组的大小
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    // 用户输入数组的元素
    printf("Enter the elements of the array (sorted in ascending order):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 用户输入目标值
    printf("Enter the target value to search for: ");
    scanf("%d", &target);

    // 调用二分查找函数
    int result = binary_search(arr, n, target);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
