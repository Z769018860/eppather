#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int s[MAXLEN] = {0};

int shellsort(int len) {
clock_t start, end;
start = clock();
    int i, j, gap, temp;

    for (gap = len / 2; gap > 0; gap = gap / 2) {
        for (i = gap; i < len; i = i + 1) {
            for (j = i - gap; j >= 0 && s[j] > s[j + gap]; j = j - gap) {
                temp = s[j + gap];
                s[j + gap] = s[j];
                s[j] = temp;
            }
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return 1;
}

int main() {
    int x,j;
    scanf("%d", &x);
    for (j=0;j<x;j++)
        s[j]=x-j;
    shellsort(x);
    for (j=0;j<x;j++)
        printf("%d ",s[j]);
    printf("\n");
    return 0;
}