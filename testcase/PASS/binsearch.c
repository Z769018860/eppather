#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

int binary_search(int n, int target) {
    int left = 0;
    int right = n - 1;
    clock_t start, end;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return -1;
}

int main() {
    int x,y,j;
    scanf("%d %d", &x, &y);
    for (j=0;j<x;j++)
        arr[j]=x-j;
    int result=binary_search(x,y);
    for (j=0;j<x;j++)
        printf("%d ",arr[j]);
    printf("\n");
    return 0;
}