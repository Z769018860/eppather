#include <stdio.h>
#include <klee/klee.h>

// 查找数组中的递增和递减序列长度
void findIncDecSequence(int arr[], int size) {
    int incLength = 1, decLength = 1;
    int i;

    // 检查递增序列
    for (i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            incLength++;
        } else {
            break;
        }
    }

    // 检查递减序列
    for (; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            decLength++;
        } else {
            break;
        }
    }

    if (incLength > 1 && decLength > 1) {
        printf("递增序列长度: %d, 递减序列长度: %d\n", incLength, decLength);
    } else {
        printf("没有找到有效的递增或递减序列。\n");
    }
}

int main() {
    int arr[7];

    // 将数组声明为符号变量
    klee_make_symbolic(arr, sizeof(arr), "arr");

    findIncDecSequence(arr, 7);

    return 0;
}
