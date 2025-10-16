#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int ar[MAXLEN] = {0};

void Insert_sort(int len) {
    clock_t start, end;
    start = clock();
    int temp = 0;
    int i, j;

    for(i = 1; i < len; i = i + 1) {
        if(ar[i] < ar[i-1]) {
            temp = ar[i];
            for(j = i - 1; j >= 0 && ar[j] > temp; j = j - 1) {
                ar[j + 1] = ar[j];
            }
            ar[j + 1] = temp;
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
        ar[j]=x-j;
    Insert_sort(x);
    for (j=0;j<x;j++)
        printf("%d ",ar[j]);
    printf("\n");
    return 0;
}