#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int data[MAXLEN] = {0};

void selectSort(int n) {
int path_len = 0;
int mems = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int min;\n");
printf("int i;\n");
printf("int j;\n");
printf("int temp;\n");
printf("int data[500000];\n");

    int min;
    int i, j;
    int temp;

    {
      int __first_iter_flag_0 = 1;
    for(i = 0; i < n - 1; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    printf("@(i < n - 1)\n");
    path_len = path_len + 1;
    
        printf("min = i;\n");
        min = i;
        
        {
          int __first_iter_flag_1 = 1;
        for(j = i + 1; j < n; j = j + 1) {
        if(__first_iter_flag_1) { 
        printf("j = i + 1;\n"); 
        __first_iter_flag_1 = 0; 
        }
        printf("@(j < n)\n");
        path_len = path_len + 1;
        
            if(data[j] < data[min]) {
            printf("@(data[j] < data[min])\n");
            path_len = path_len + 1;
            
                printf("min = j;\n");
                min = j;
                
            }
        printf("j = j + 1;\n");
}
}


        if(data[i] != data[min]) {
        printf("@(data[i] != data[min])\n");
        path_len = path_len + 1;
        
            printf("temp = data[i];\n");
            temp = data[i];
            mems = mems + 1;
            
            printf("data[i] = data[min];\n");
            data[i] = data[min];
            mems = mems + 2;
            
            printf("data[min] = temp;\n");
            data[min] = temp;
            mems = mems + 1;
            
        }
    printf("i = i + 1;\n");
}
}

    printf("\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
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
