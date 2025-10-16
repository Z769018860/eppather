#include <stdio.h>
#include <klee/klee.h>

// 检查并翻转位操作
int flipAndCheckBits(int num) {
    int result = 0;

    // 条件1：如果最高位为1，则翻转所有位
    if ((num & (1 << 31)) != 0) {
        num = ~num;  // 翻转所有位
    }

    // 条件2：检查是否有连续的三个1
    if ((num & 0b111) == 0b111) {
        result += num;  // 如果有三个连续的1，增加结果
    }

    // 条件3：逐位检查是否为质数
    for (int i = 0; i < 32; i++) {
        if ((num & (1 << i)) != 0) {
            int bitValue = 1 << i;
            int isPrime = 1;
            for (int j = 2; j * j <= bitValue; j++) {
                if (bitValue % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime) {
                result += bitValue;
            }
        }
    }

    return result;
}

// 处理数组中的每个元素
int processArrayWithFlip(int arr[], int size) {
    int totalSum = 0;

    for (int i = 0; i < size; i++) {
        totalSum += flipAndCheckBits(arr[i]);

        // 条件4：如果当前元素和前一个元素翻转后相同，增加结果
        if (i > 0 && (~arr[i] == arr[i - 1])) {
            totalSum += arr[i];
        }

        // 条件5：检查最高四位是否全为1
        if ((arr[i] & 0xF0000000) == 0xF0000000) {
            totalSum += arr[i] * 2;
        }
    }

    return totalSum;
}

int main() {
    int arr[5];
    int size;

    // 将数组和size声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");
    klee_make_symbolic(&size, sizeof(size), "size");

    // 限制size的范围在1到10之间
    //klee_assume(size > 0 && size <= 5);

    // 调用函数处理数组
    int result = processArrayWithFlip(arr, size);
    printf("处理结果总和: %d\n", result);

    return 0;
}
