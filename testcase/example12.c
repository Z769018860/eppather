#include <stdio.h>
#include <klee/klee.h>

// 对整数应用位掩码和位运算
int processWithBitOperations(int num, int mask) {
    int result = 0;

    // 条件1：检查奇数位是否全为1
    if ((num & 0xAAAAAAAA) == 0xAAAAAAAA) {
        result += num;
    }

    // 条件2：检查偶数位是否全为0
    if ((num & 0x55555555) == 0) {
        result += num >> 1;  // 右移1位并增加结果
    }

    // 条件3：应用掩码并检查是否为质数
    int masked = num & mask;
    if (masked > 1) {
        int isPrime = 1;
        for (int i = 2; i * i <= masked; i++) {
            if (masked % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            result += masked;
        }
    }

    return result;
}

// 处理数组并返回总和
int processArray(int arr[], int size, int mask) {
    int totalSum = 0;

    for (int i = 0; i < size; i++) {
        totalSum += processWithBitOperations(arr[i], mask);

        // 条件4：检查元素的前后位是否匹配
        if (i > 0 && (arr[i] & arr[i - 1]) == 0) {
            totalSum += arr[i];
        }

        // 条件5：检查是否是两次右移后的结果与掩码相同
        if ((arr[i] >> 2) == mask) {
            totalSum += arr[i] * 2;
        }
    }

    return totalSum;
}

int main() {
    int arr[5];
    int mask;
    int size;

    // 将数组、掩码和size声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");
    klee_make_symbolic(&mask, sizeof(mask), "mask");
    klee_make_symbolic(&size, sizeof(size), "size");

    // 限制size的范围在1到10之间
    //klee_assume(size > 0 && size <= 5);

    // 调用函数处理数组
    int result = processArray(arr, size, mask);
    printf("处理结果总和: %d\n", result);

    return 0;
}
