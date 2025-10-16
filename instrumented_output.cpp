#include <stdio.h>
printf("Executing statement: \n");

// 函数：冒泡排序
void bubbleSort(int arr[], intprinpriprinprinpriprintf("Executing statement: i\n");
printf("Executing statement: i++\n"prinpriprinprinprinpriprintf("Executing stateprinprintprinprinprintf("Executing statement: 1\n");
tf("Executing statement: j\n");
prprintf(prinprintf("Executing stprinprintprinprinprintf("Executing stprinprinprintprintf("Executing statement: temp\n");
printf("Executing statement: temp\n");printf("Executing statement: 5\pripprprprprprintf("Executing statement: 3\n");
intf(printf("Exeprintprintf("Executing statement: n\n");
printprintf(printf("Executing statement: "Sortedpriprinpriprintf("Executiprintf(printf(prinprintf("Executiprintf(printf("Executing sprintf("Executing statement: 0\n");
tatement: "\n"\n");
printf("Executing statement: "\n"\n");
"Executing statement: printf\n");
printf("Executing statement: printf\n");
printf("Executing statement: printf("\n")\n");
ng statement: i\n");
printf("Executing statement: i\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[i]\n");
printf("Executing statement: arr[i]\n");
"Executing statement: "%d "\n");
printf("Executing statement: "%d "\n");
"Executing statement: printf\n");
printf("Executing statement: printf\n");
printf("Executing statement: printf("%d ", arr[i])\n");
ng statement: i\n");
printf("Executing statement: i++\n");
ntf("Executing statement: n\n");
printf("Executing statement: n\n");
tf("Executing statement: i\n");
printf("Executing statement: i\n");
printf("Executing statement: i < n\n");
ntf("Executing statement: 0\n");
 array: "\n");
printf("Executing statement: "Sorted array: "\n");
"Executing statement: printf\n");
printf("Executing statement: printf\n");
printf("Executing statement: printf("Sorted array: ")\n");
f("Executing statement: n\n");
f("Executing statement: arr\n");
printf("Executing statement: arr\n");
cuting statement: bubbleSort\n");
printf("Executing statement: bubbleSort\n");
printf("Executing statement: bubbleSort(arr, n)\n");
"Executing statement: 4\n");
intf("Executing statement: 2\n");
intf("Executing statement: 5\n");
intf("Executing statement: 1\n");
rintf("Executing statement: {1,5,2,4,3}\n");
ntf("Executing statement: 5\n");
n");

f("Executing statement: 1\n");
tf("Executing statement: j\n");
printf("Executing statement: j\n");
printf("Executing statement: j + 1\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j + 1]\n");
printf("Executing statement: arr[j + 1] = temp\n");
atement: 1\n");
tf("Executing statement: j\n");
printf("Executing statement: j\n");
printf("Executing statement: j + 1\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j + 1]\n");
printf("Executing statement: arr[j + 1]\n");
f("Executing statement: j\n");
printf("Executing statement: j\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j]\n");
printf("Executing statement: arr[j] = arr[j + 1]\n");
atement: j\n");
printf("Executing statement: j\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j]\n");
printf("Executing statement: arr[j]\n");
"Executing statement: temp\n");
printf("Executing statement: temp = arr[j]\n");
intf("Executing statement: j\n");
printf("Executing statement: j + 1\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j + 1]\n");
printf("Executing statement: arr[j + 1]\n");
f("Executing statement: j\n");
printf("Executing statement: j\n");
tf("Executing statement: arr\n");
printf("Executing statement: arr\n");
printf("Executing statement: arr[j]\n");
printf("Executing statement: arr[j]\n");
printf("Executing statement: arr[j] > arr[j + 1]\n");
ment: j\n");
printf("Executing statement: j++\n");
ntf("Executing statement: 1\n");
tf("Executing statement: i\n");
printf("Executing statement: i\n");
tf("Executing statement: n\n");
printf("Executing statement: n\n");
printf("Executing statement: n - i\n");
printf("Executing statement: n - i - 1\n");
tf("Executing statement: j\n");
printf("Executing statement: j\n");
printf("Executing statement: j < n - i - 1\n");
ntf("Executing statement: 0\n");
tf("Executing statement: j\n");
printf("Executing statement: j = 0\n");
);
ntf("Executing statement: 1\n");
tf("Executing statement: n\n");
printf("Executing statement: n\n");
printf("Executing statement: n - 1\n");
tf("Executing statement: i\n");
printf("Executing statement: i\n");
printf("Executing statement: i < n - 1\n");
ntf("Executing statement: 0\n");
tf("Executing statement: i\n");
printf("Executing statement: i = 0\n");
 n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // 最后 i 个元素已经是排好序的
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 主函数
intprintf("Executing statement: 4\n");
 main() {
    int n = 5; // 数组大小
    int arr[5]={1,5,2,4,3};

    // 调用冒泡排序算法
    bubbleSort(arr, n);

    // 输出排序后的数组
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}