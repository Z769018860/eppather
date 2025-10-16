#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int ar[MAXLEN] = {0};

void Insert_sort(int len) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
printf("Path: \n");
printf("int len;\n");
printf("int temp;\n");
printf("int i;\n");
printf("int j;\n");
printf("double time_taken;\n");
printf("int ar[500000];\n");

    clock_t start, end;
    printf("start = clock();\n");
    start = clock();
    
    int temp = 0;
    int i, j;

    {
      int __first_iter_flag_0 = 1;
    for(i = 1; i < len; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 1;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < len)\n");
    path_len = path_len + 1;
    
        if(ar[i] < ar[i-1]) {
        cond_count = cond_count + 1;
        printf("@(ar[i] < ar[i-1])\n");
        path_len = path_len + 1;
        mems = mems + 2;
        
            printf("temp = ar[i];\n");
            temp = ar[i];
            mems = mems + 1;
            
            {
              int __first_iter_flag_1 = 1;
            for(j = i - 1; j >= 0 && ar[j] > temp; j = j - 1) {
            if(__first_iter_flag_1) { 
            printf("j = i - 1;\n"); 
            __first_iter_flag_1 = 0; 
            }
            cond_count = cond_count + 1;
            printf("@(j >= 0 && ar[j] > temp)\n");
            path_len = path_len + 1;
            mems = mems + 1;
            
                printf("ar[j + 1] = ar[j];\n");
                ar[j + 1] = ar[j];
                mems = mems + 2;
                
            printf("j = j - 1;\n");
}
}

            printf("ar[j + 1] = temp;\n");
            ar[j + 1] = temp;
            mems = mems + 1;
            
        }
    printf("i = i + 1;\n");
}
}


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
        ar[j]=x-j;
    Insert_sort(x);
    for (j=0;j<x;j++)
        printf("%d ",ar[j]);
    printf("\n");
    return 0;
}