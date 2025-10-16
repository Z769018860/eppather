#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int s[MAXLEN] = {0};

int shellsort(int len) {
int path_len = 0;
int mems = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int len;\n");
printf("int i;\n");
printf("int j;\n");
printf("int gap;\n");
printf("int temp;\n");
printf("int s[500000];\n");

    int i, j, gap, temp;

    {
      int __first_iter_flag_0 = 1;
    for (gap = len / 2; gap > 0; gap = gap / 2) {
    if(__first_iter_flag_0) { 
    printf("gap = len / 2;\n"); 
    __first_iter_flag_0 = 0; 
    }
    printf("@(gap > 0)\n");
    path_len = path_len + 1;
    
        {
          int __first_iter_flag_1 = 1;
        for (i = gap; i < len; i = i + 1) {
        if(__first_iter_flag_1) { 
        printf("i = gap;\n"); 
        __first_iter_flag_1 = 0; 
        }
        printf("@(i < len)\n");
        path_len = path_len + 1;
        
            {
              int __first_iter_flag_2 = 1;
            for (j = i - gap; j >= 0 && s[j] > s[j + gap]; j = j - gap) {
            if(__first_iter_flag_2) { 
            printf("j = i - gap;\n"); 
            __first_iter_flag_2 = 0; 
            }
            printf("@(j >= 0 && s[j] > s[j + gap])\n");
            path_len = path_len + 1;
            
                printf("temp = s[j + gap];\n");
                temp = s[j + gap];
                mems = mems + 1;
                
                printf("s[j + gap] = s[j];\n");
                s[j + gap] = s[j];
                mems = mems + 2;
                
                printf("s[j] = temp;\n");
                s[j] = temp;
                mems = mems + 1;
                
            printf("j = j - gap;\n");
}
}

        printf("i = i + 1;\n");
}
}

    printf("gap = gap / 2;\n");
}
}

    printf("\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
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