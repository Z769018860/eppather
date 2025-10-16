#include <stdio.h>
#include <klee/klee.h>

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n) {
    int p1 = m - 1;
    int p2 = n - 1;
    int p = m + n - 1;

    // 合并两个数组，比较从后往前的元素
    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] > nums2[p2]) {
            nums1[p] = nums1[p1];
            p1 = p1 - 1;
        } else {
            nums1[p] = nums2[p2];
            p2 = p2 - 1;
        }
        p = p - 1;
    }

    // 如果 nums2 还有剩余，继续填充 nums1
    while (p2 >= 0) {
        nums1[p] = nums2[p2];
        p2 = p2 - 1;
        p = p - 1;
    }
}

int main() {
    int nums1[10], nums2[5];
    int nums1Size = 10, nums2Size = 5;
    int m = 5, n = 5;

    // 使用 KLEE 符号化输入数组
    klee_make_symbolic(nums1, sizeof(nums1), "nums1");
    klee_make_symbolic(nums2, sizeof(nums2), "nums2");

    // 调用 merge 函数
    merge(nums1, nums1Size, m, nums2, nums2Size, n);

    // 输出合并后的 nums1 数组
    printf("Merged array: ");
    for (int i = 0; i < nums1Size; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");

    return 0;
}
