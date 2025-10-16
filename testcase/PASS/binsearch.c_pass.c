#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

int binary_search(int n, int target) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int target;\n");
printf("int left;\n");
printf("int right;\n");
printf("double time_taken;\n");
printf("int arr[500000];\n");

    int left = 0;
    int right = n - 1;
    while (left <= right) {
    cond_count = cond_count + 1;
    printf("@(left <= right)\n");
    path_len = path_len + 1;
    
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
        cond_count = cond_count + 1;
        printf("@(arr[mid] == target)\n");
        path_len = path_len + 1;
        mems = mems + 1;
        
            printf("\nEND\nTotal path length: %d\n", path_len);
            printf("Total memory accesses: %d\n", mems);
            printf("Total conditional statements: %d\n", cond_count);
            return mid;
        }
        else {

        cond_count = cond_count + 1;
        printf("@(!(arr[mid] == target))\n");
        path_len = path_len + 1;
        mems = mems + 1;
        if (arr[mid] < target) {
        cond_count = cond_count + 1;
        printf("@(arr[mid] < target)\n");
        path_len = path_len + 1;
        mems = mems + 1;
        
            printf("left = mid + 1;\n");
            left = mid + 1;
            
        }
        else {
        cond_count = cond_count + 1;
        printf("@(!(arr[mid] < target))\n");
        path_len = path_len + 1;
        mems = mems + 1;
        
            printf("right = mid - 1;\n");
            right = mid - 1;
            
        }
}
    }
    printf("end = clock();\n");
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    printf("\nEND\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    printf("Total conditional statements: %d\n", cond_count);
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