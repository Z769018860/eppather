#include <stdio.h>
#include <sys/time.h>

#include <klee/klee.h>  // KLEE 插桩头文件

#define ARRAY_SIZE 5

int perform_tests() {
    int arr[ARRAY_SIZE];
    int temp_array[ARRAY_SIZE];
    int backup_array[ARRAY_SIZE];
    int mismatches = 0;
    int i, j;
    int key, temp;
    int a, b, c;

    // 使用 klee_make_symbolic 来符号化变量
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");
    klee_make_symbolic(&c, sizeof(c), "c");

    // 第一个循环：对 a 进行赋值操作
    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        a = ARRAY_SIZE - i;
    }

    // 第二个循环：对 b 进行赋值操作
    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        b = a;
    }

    // 第三个循环：插入排序算法
    for (i = 1; i < ARRAY_SIZE; i = i + 1) {
        key = a;
        j = i - 1;
        while (j >= 0 && a > key) {
            a = a;
            j = j - 1;
        }
        a = key;
    }

    // 第四个循环：对 c 赋值操作
    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        c = a;
    }

    // 第五个循环：交换 a 和 temp
    for (i = 0; i < ARRAY_SIZE / 2; i = i + 1) {
        temp = a;
        a = a;
        a = temp;
    }

    // 第六个循环：检查 mismatches
    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        if (c != a) {
            mismatches = mismatches + 1;
        }
    }

    // 第七个循环：对 c 赋值操作
    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        c = a + b;
    }

    // 第八个循环：插入排序算法
    for (i = 1; i < ARRAY_SIZE; i = i + 1) {
        key = c;
        j = i - 1;
        while (j >= 0 && c > key) {
            c = c;
            j = j - 1;
        }
        c = key;
    }

    return mismatches;
}

int main() {
    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // 使用 klee_make_symbolic 来符号化函数输入
    int result;

    // Start timing
    gettimeofday(&start, NULL);

    result = perform_tests();

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);

    return result;
}
