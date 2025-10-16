#include <stdio.h>
#include <klee/klee.h>

// 执行复杂的数组操作，圈复杂度 >= 20
int complexArrayUnitFunction(int arr[], int size) {
    int result = 0;
    int sumPositive = 0;
    int sumNegative = 0;

    // 遍历数组
    for (int i = 0; i < size; i++) {
        // 条件1：正数
        if (arr[i] > 0) {
            sumPositive += arr[i];

            // 条件2：如果是偶数，做进一步处理
            if (arr[i] % 2 == 0) {
                result += arr[i] * 2;  // 偶数翻倍
            }

            // 条件3：如果大于前一个元素
            if (i > 0 && arr[i] > arr[i - 1]) {
                result += arr[i] - arr[i - 1];  // 增加差值
            }
        }

        // 条件4：负数
        else if (arr[i] < 0) {
            sumNegative += arr[i];

            // 条件5：负数且是奇数
            if (arr[i] % 2 != 0) {
                result += arr[i] * 3;  // 奇数负数乘3
            }

            // 条件6：负数比后一个元素小
            if (i < size - 1 && arr[i] < arr[i + 1]) {
                result -= arr[i];  // 增加其负值
            }
        }

        // 条件7：数组元素大于其前后元素的和
        if (i > 0 && i < size - 1 && arr[i] > arr[i - 1] + arr[i + 1]) {
            result += arr[i] * 5;
        }
    }

    // 条件8：根据正负数总和做额外处理
    if (sumPositive > -sumNegative) {
        result += sumPositive;
    } else {
        result += sumNegative;
    }

    return result;
}

int main() {
    int arr[5];
    int size;

    // 将数组声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");

    // 将size声明为符号变量并限定其范围
    klee_make_symbolic(&size, sizeof(size), "size");
    //klee_assume(size > 0 && size <= 5);

    // 调用复杂数组操作函数
    int result = complexArrayUnitFunction(arr, size);

    // 打印结果
    printf("计算结果: %d\n", result);

    return 0;
}
