#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

void bubbleSort( int n) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int i;\n");
printf("int j;\n");
printf("int temp;\n");
printf("double time_taken;\n");
printf("int arr[500000];\n");

    
    int i, j, temp;
    {
      int __first_iter_flag_0 = 1;
    for (i = 0; i < n - 1; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < n - 1)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_1 = 1;
        for (j = 0; j < n - i - 1; j = j + 1) {
        if(__first_iter_flag_1) { 
        printf("j = 0;\n"); 
        __first_iter_flag_1 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(j < n - i - 1)\n");
        path_len = path_len + 1;
        
            if (arr[j] > arr[j + 1]) {
            cond_count = cond_count + 1;
            printf("@(arr[j] > arr[j + 1])\n");
            path_len = path_len + 1;
            mems = mems + 2;
            
                printf("temp = arr[j];\n");
                temp = arr[j];
                mems = mems + 1;
                
                printf("arr[j] = arr[j + 1];\n");
                arr[j] = arr[j + 1];
                mems = mems + 2;
                
                printf("arr[j + 1] = temp;\n");
                arr[j + 1] = temp;
                mems = mems + 1;
                
            }
        printf("j = j + 1;\n");
}
}

    printf("i = i + 1;\n");
}
}

    printf("end = clock();\n");
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    printf("\nEND\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    printf("Total conditional statements: %d\n", cond_count);
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