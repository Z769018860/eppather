#include <stdio.h>

// 单元函数：计算波峰和波谷的数量
int countPeaksAndValleys(int arr[5], int size) {
    if (size < 3) 
        return 0;
    int count = 0;

    for (int i = 1; i < size - 1; i=i+1) {
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                count=count+1; 
            }
            ;
        }

        else if (arr[i] < arr[i - 1]) {
            if (arr[i] < arr[i + 1]) {
                count=count+1; 
            }
            ;
        }
    }

    return count;
}

int main() {
    // 测试用例 1
    int arr1[5] = {0, 3, 1, 2, 1};
    int size1 = 5;
    int result1 = countPeaksAndValleys(arr1, size1);
    printf("Test Case 1: Peaks and Valleys Count = %d\n", result1);

    // 测试用例 2
    int arr2[2] = {0,1};
    int size2 = 2;
    int result2 = countPeaksAndValleys(arr2, size2);
    printf("Test Case 2: Peaks and Valleys Count = %d\n", result2);

    // 测试用例 3
    int arr3[4] = {3, 2, 2, 2};
    int size3 = 4;
    int result3 = countPeaksAndValleys(arr3, size3);
    printf("Test Case 3: Peaks and Valleys Count = %d\n", result3);

    // 测试用例 4
    int arr4[4] = {1,2,3,2};
    int size4 = 4;
    int result4 = countPeaksAndValleys(arr4, size4);
    printf("Test Case 4: Peaks and Valleys Count = %d\n", result4);

    return 0;
}
