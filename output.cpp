#include <stdio.h>

// 函数：冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (printf("Executing statement: i = 0\n");
    printf("Executing statement: i\n");
    i = printf("Executing statement: 0\n");
    0; printf("Executing statement: i < n - 1\n");
    printf("Executing statement: i\n");
    printf("Executing statement: i\n");
    i < printf("Executing statement: n - 1\n");
    printf("Executing statement: n\n");
    printf("Executing statement: n\n");
    n - printf("Executing statement: 1\n");
    1; printf("Executing statement: i++\n");
    printf("Executing statement: i\n");
    i++) {
        // 最后 i 个元素已经是排好序的
        for (printf("Executing statement: j = 0\n");
        printf("Executing statement: j\n");
        j = printf("Executing statement: 0\n");
        0; printf("Executing statement: j < n - i - 1\n");
        printf("Executing statement: j\n");
        printf("Executing statement: j\n");
        j < printf("Executing statement: n - i - 1\n");
        printf("Executing statement: n - i\n");
        printf("Executing statement: n\n");
        printf("Executing statement: n\n");
        n - printf("Executing statement: i\n");
        printf("Executing statement: i\n");
        i - printf("Executing statement: 1\n");
        1; printf("Executing statement: j++\n");
        printf("Executing statement: j\n");
        j++) {
            if (printf("Executing statement: arr[j] > arr[j + 1]\n");
            printf("Executing statement: arr[j]\n");
            printf("Executing statement: arr[j]\n");
            printf("Executing statement: arr\n");
            printf("Executing statement: arr\n");
            arr[printf("Executing statement: j\n");
            printf("Executing statement: j\n");
            j] > printf("Executing statement: arr[j + 1]\n");
            printf("Executing statement: arr[j + 1]\n");
            printf("Executing statement: arr\n");
            printf("Executing statement: arr\n");
            arr[printf("Executing statement: j + 1\n");
            printf("Executing statement: j\n");
            printf("Executing statement: j\n");
            j + printf("Executing statement: 1\n");
            1]) {
                // 交换 arr[j] 和 arr[j + 1]
                printf("Executing statement: temp = arr[j]\n");
                printf("Executing statement: temp\n");
                temp = printf("Executing statement: arr[j]\n");
                printf("Executing statement: arr[j]\n");
                printf("Executing statement: arr\n");
                printf("Executing statement: arr\n");
                arr[printf("Executing statement: j\n");
                printf("Executing statement: j\n");
                j];
                printf("Executing statement: arr[j] = arr[j + 1]\n");
                printf("Executing statement: arr[j]\n");
                printf("Executing statement: arr\n");
                printf("Executing statement: arr\n");
                arr[printf("Executing statement: j\n");
                printf("Executing statement: j\n");
                j] = printf("Executing statement: arr[j + 1]\n");
                printf("Executing statement: arr[j + 1]\n");
                printf("Executing statement: arr\n");
                printf("Executing statement: arr\n");
                arr[printf("Executing statement: j + 1\n");
                printf("Executing statement: j\n");
                printf("Executing statement: j\n");
                j + printf("Executing statement: 1\n");
                1];
                printf("Executing statement: arr[j + 1] = temp\n");
                printf("Executing statement: arr[j + 1]\n");
                printf("Executing statement: arr\n");
                printf("Executing statement: arr\n");
                arr[printf("Executing statement: j + 1\n");
                printf("Executing statement: j\n");
                printf("Executing statement: j\n");
                j + printf("Executing statement: 1\n");
                1] = printf("Executing statement: temp\n");
                printf("Executing statement: temp\n");
                temp;
            }
        }
    }
}

// 主函数
int main() {
    int n = printf("Executing statement: 5\n");
    5; // 数组大小
    int arr[printf("Executing statement: 5\n");
    5]=printf("Executing statement: {1,5,2,4,3}\n");
    {printf("Executing statement: 1\n");
    1,printf("Executing statement: 5\n");
    5,printf("Executing statement: 2\n");
    2,printf("Executing statement: 4\n");
    4,printf("Executing statement: 3\n");
    3};

    // 调用冒泡排序算法
    printf("Executing statement: bubbleSort(arr, n)\n");
    printf("Executing statement: bubbleSort\n");
    printf("Executing statement: bubbleSort\n");
    bubbleSort(printf("Executing statement: arr\n");
    printf("Executing statement: arr\n");
    arr, printf("Executing statement: n\n");
    printf("Executing statement: n\n");
    n);

    // 输出排序后的数组
    printf("Executing statement: printf("Sorted array: ")\n");
    printf("Executing statement: printf\n");
    printf("Executing statement: printf\n");
    printf(printf("Executing statement: "Sorted array: "\n");
    printf("Executing statement: "Sorted array: "\n");
    "Sorted array: ");
    for (int i = printf("Executing statement: 0\n");
    0; printf("Executing statement: i < n\n");
    printf("Executing statement: i\n");
    printf("Executing statement: i\n");
    i < printf("Executing statement: n\n");
    printf("Executing statement: n\n");
    n; printf("Executing statement: i++\n");
    printf("Executing statement: i\n");
    i++) {
        printf("Executing statement: printf("%d ", arr[i])\n");
        printf("Executing statement: printf\n");
        printf("Executing statement: printf\n");
        printf(printf("Executing statement: "%d "\n");
        printf("Executing statement: "%d "\n");
        "%d ", printf("Executing statement: arr[i]\n");
        printf("Executing statement: arr[i]\n");
        printf("Executing statement: arr\n");
        printf("Executing statement: arr\n");
        arr[printf("Executing statement: i\n");
        printf("Executing statement: i\n");
        i]);
    }
    printf("Executing statement: printf("\n")\n");
    printf("Executing statement: printf\n");
    printf("Executing statement: printf\n");
    printf(printf("Executing statement: "\n"\n");
    printf("Executing statement: "\n"\n");
    "\n");

    return printf("Executing statement: 0\n");
    0;
}