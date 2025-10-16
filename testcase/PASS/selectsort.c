#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int data[MAXLEN] = {0};

void selectSort(int n) {
clock_t start, end;
start = clock();
    int min;
    int i, j;
    int temp;

    for(i = 0; i < n - 1; i = i + 1) {
        min = i;
        for(j = i + 1; j < n; j = j + 1) {
            if(data[j] < data[min]) {
                min = j;
            }
        }

        if(data[i] != data[min]) {
            temp = data[i];
            data[i] = data[min];
            data[min] = temp;
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
        data[j]=x-j;
    selectSort(x);
    for (j=0;j<x;j++)
        printf("%d ",data[j]);
    printf("\n");
    return 0;
}
