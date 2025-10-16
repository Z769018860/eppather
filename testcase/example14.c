#include <stdio.h>
#include <klee/klee.h>

// 检查并翻转位操作
int flipAndCheckBitsUnit(int num) {
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

int main() {
    int num;

    // 将num声明为符号变量
    klee_make_symbolic(&num, sizeof(num), "num");

    // 调用单元函数处理单个整数
    int result = flipAndCheckBitsUnit(num);
    printf("处理结果: %d\n", result);

    return 0;
}
