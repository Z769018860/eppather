#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <klee/klee.h>  // KLEE 插桩头文件

void complex_array_manipulations(int arr[10], int size) {
    int i;
    int j;
    int temp;

    // 使用 klee_make_symbolic 来进行符号化
    klee_make_symbolic(&size, sizeof(size), "size");
    //klee_assume(size >= 0 && size <= 10); // 假设数组大小在合理范围内

    klee_make_symbolic(arr, sizeof(int) * size, "arr");

    // 根据 arr[0] 的值进行不同的处理
    if (arr[0] % 2 == 0) {
        for (i = 0; i < size / 2; i = i + 1) {
            temp = arr[i];
            arr[i] = arr[size - i - 1];
            arr[size - i - 1] = temp;
        }
    } else {
        for (i = 0; i < size; i = i + 1) {
            arr[i] = arr[i] * arr[i];
        }
    }

    // 处理 arr[0] + arr[size-1] 的值
    if ((arr[0] + arr[size - 1]) > 100) {
        for (i = 0; i < size; i = i + 1) {
            for (j = i + 1; j < size; j = j + 1) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    } else {
        int max = arr[0];
        for (i = 1; i < size; i = i + 1) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        for (i = 0; i < size; i = i + 1) {
            arr[i] = max;
        }
    }

    // 特殊处理，当 size > 5 且 arr[5] 是 10 的倍数时
    if (size > 5 && arr[5] % 10 == 0) {
        for (i = 0; i < size / 2; i = i + 1) {
            arr[i] = arr[i] * 2;
        }
    }
    return;
}

int main() {
    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // 使用 klee_make_symbolic 来符号化数组 arr 和 size
    int arr[10];
    int size = 2;

    klee_make_symbolic(arr, sizeof(arr), "arr");

    gettimeofday(&start, NULL);
    complex_array_manipulations(arr, size);
    gettimeofday(&end, NULL);

    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
    return 0;
}
