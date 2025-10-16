#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

void bubbleSort( int n) {
    clock_t start, end;
    start = clock();
    int i, j, temp;
    for (i = 0; i < n - 1; i = i + 1) {
        for (j = 0; j < n - i - 1; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return;
}

int main() {
    int x,j;
    scanf("%d", &x);
    for (j=0;j<x;j++)
        arr[j]=x-j;
    bubbleSort(x);
    for (j=0;j<x;j++)
        printf("%d ",arr[j]);
    printf("\n");
    return 0;
}