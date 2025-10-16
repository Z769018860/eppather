#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

void complex_array_manipulations(int size) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int size;\n");
printf("int i;\n");
printf("int j;\n");
printf("int temp;\n");
printf("double time_taken;\n");
printf("int arr[500000];\n");
    
    int i;
    int j;
    int temp;


    if (arr[0] % 2 == 0) {
    cond_count = cond_count + 1;
    printf("@(arr[0] % 2 == 0)\n");
    path_len = path_len + 1;
    mems = mems + 1;
    
        {
          int __first_iter_flag_0 = 1;
        for (i = 0; i < size / 2; i = i + 1) {
        if(__first_iter_flag_0) { 
        printf("i = 0;\n"); 
        __first_iter_flag_0 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size / 2)\n");
        path_len = path_len + 1;
        
            printf("temp = arr[i];\n");
            temp = arr[i];
            mems = mems + 1;
            
            printf("arr[i] = arr[size - i - 1];\n");
            arr[i] = arr[size - i - 1];
            mems = mems + 2;
            
            printf("arr[size - i - 1] = temp;\n");
            arr[size - i - 1] = temp;
            mems = mems + 1;
            
        printf("i = i + 1;\n");
}
}

    } else {
    cond_count = cond_count + 1;
    printf("@(!(arr[0] % 2 == 0))\n");
    path_len = path_len + 1;
    mems = mems + 1;
    
        {
          int __first_iter_flag_1 = 1;
        for (i = 0; i < size; i = i + 1) {
        if(__first_iter_flag_1) { 
        printf("i = 0;\n"); 
        __first_iter_flag_1 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size)\n");
        path_len = path_len + 1;
        
            printf("arr[i] = arr[i] * arr[i];\n");
            arr[i] = arr[i] * arr[i];
            mems = mems + 3;
            
        printf("i = i + 1;\n");
}
}

    }

    if ((arr[0] + arr[size - 1]) > 100) {
    cond_count = cond_count + 1;
    printf("@((arr[0] + arr[size - 1]) > 100)\n");
    path_len = path_len + 1;
    mems = mems + 2;
    
        {
          int __first_iter_flag_2 = 1;
        for (i = 0; i < size; i = i + 1) {
        if(__first_iter_flag_2) { 
        printf("i = 0;\n"); 
        __first_iter_flag_2 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size)\n");
        path_len = path_len + 1;
        
            {
              int __first_iter_flag_3 = 1;
            for (j = i + 1; j < size; j = j + 1) {
            if(__first_iter_flag_3) { 
            printf("j = i + 1;\n"); 
            __first_iter_flag_3 = 0; 
            }
            cond_count = cond_count + 1;
            printf("@(j < size)\n");
            path_len = path_len + 1;
            
                if (arr[i] > arr[j]) {
                cond_count = cond_count + 1;
                printf("@(arr[i] > arr[j])\n");
                path_len = path_len + 1;
                mems = mems + 2;
                
                    printf("temp = arr[i];\n");
                    temp = arr[i];
                    mems = mems + 1;
                    
                    printf("arr[i] = arr[j];\n");
                    arr[i] = arr[j];
                    mems = mems + 2;
                    
                    printf("arr[j] = temp;\n");
                    arr[j] = temp;
                    mems = mems + 1;
                    
                }
            printf("j = j + 1;\n");
}
}

        printf("i = i + 1;\n");
}
}

    } else {
    cond_count = cond_count + 1;
    printf("@(!((arr[0] + arr[size - 1]) > 100))\n");
    path_len = path_len + 1;
    mems = mems + 2;
    
        int max = arr[0];
        {
          int __first_iter_flag_4 = 1;
        for (i = 1; i < size; i = i + 1) {
        if(__first_iter_flag_4) { 
        printf("i = 1;\n"); 
        __first_iter_flag_4 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size)\n");
        path_len = path_len + 1;
        
            if (arr[i] > max) {
            cond_count = cond_count + 1;
            printf("@(arr[i] > max)\n");
            path_len = path_len + 1;
            mems = mems + 1;
            
                printf("max = arr[i];\n");
                max = arr[i];
                mems = mems + 1;
                
            }
        printf("i = i + 1;\n");
}
}

        {
          int __first_iter_flag_5 = 1;
        for (i = 0; i < size; i = i + 1) {
        if(__first_iter_flag_5) { 
        printf("i = 0;\n"); 
        __first_iter_flag_5 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size)\n");
        path_len = path_len + 1;
        
            printf("arr[i] = max;\n");
            arr[i] = max;
            mems = mems + 1;
            
        printf("i = i + 1;\n");
}
}

    }

    if (size > 5 && arr[5] % 10 == 0) {
    cond_count = cond_count + 1;
    printf("@(size > 5 && arr[5] % 10 == 0)\n");
    path_len = path_len + 1;
    mems = mems + 1;
    
        {
          int __first_iter_flag_6 = 1;
        for (i = 0; i < size / 2; i = i + 1) {
        if(__first_iter_flag_6) { 
        printf("i = 0;\n"); 
        __first_iter_flag_6 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(i < size / 2)\n");
        path_len = path_len + 1;
        
            printf("arr[i] = arr[i] * 2;\n");
            arr[i] = arr[i] * 2;
            mems = mems + 2;
            
        printf("i = i + 1;\n");
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
    return;
}

int main() {
    int x,j;
    scanf("%d", &x);
    complex_array_manipulations(x);
    for (j=0;j<x;j++)
        printf("%d ",arr[j]);
    printf("\n");
    return 0;
}