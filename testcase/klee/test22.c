#include <stdio.h>
#include <klee/klee.h>  // 引入 KLEE 插桩库

void Insert_sort(int ar[5], int len) {
    int temp = 0;
    int i, j;

    // KLEE 插桩：将 ar 数组和 len 设为符号输入
    klee_make_symbolic(ar, sizeof(int) * 5, "ar");  // 数组 ar 为符号输入
    klee_make_symbolic(&len, sizeof(len), "len");  // 变量 len 为符号输入

    // 插入排序
    for(i = 1; i < len; i = i + 1) {
        if(ar[i] < ar[i-1]) {
            temp = ar[i];
            for(j = i - 1; j >= 0 && ar[j] > temp; j = j - 1) {
                ar[j + 1] = ar[j];
            }
            ar[j + 1] = temp;
        }
    }
    return;
}

int main() {
    int ar[5];   // 数组 ar 为输入参数
    int len;     // len 作为输入参数

    // KLEE 插桩：将 ar 数组和 len 设为符号输入
    klee_make_symbolic(ar, sizeof(int) * 5, "ar");  // 数组 ar 为符号输入
    klee_make_symbolic(&len, sizeof(len), "len");  // 变量 len 为符号输入

    // 调用插入排序函数
    Insert_sort(ar, len);

    // 打印排序后的数组
    printf("Sorted array: ");
    for(int i = 0; i < len; i++) {
        printf("%d ", ar[i]);
    }
    printf("\n");

    return 0;
}
