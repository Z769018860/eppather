#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

void test(int n,int mode) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int mode;\n");
printf("int a;\n");
printf("int b;\n");
printf("int i;\n");
printf("int arr[500000];\n");

    int a = 0, b = 0;
    int i;

    {
      int __first_iter_flag_0 = 1;
    for(i=0; i<n; i++) {
    if(__first_iter_flag_0) { 
    printf("i=0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i<n)\n");
    path_len = path_len + 1;
                    
        if(mode>0){
        cond_count = cond_count + 1;
        printf("@(mode>0)\n");
        path_len = path_len + 1;
        
            printf("arr[i] = i * 2+arr[i];\n");
            arr[i] = i * 2+arr[i];
            mems = mems + 2;
                          
            printf("mode=mode-1;\n");
            mode=mode-1;
                              
        } else {
        cond_count = cond_count + 1;
        printf("@(!(mode>0))\n");
        path_len = path_len + 1;
        
            printf("b = i * 3+b;\n");
            b = i * 3+b;
                              
            printf("mode=mode-1;\n");
            mode=mode-1;
                                   
        }
    printf("i++;\n");
}
}

    printf("%d %d",a,b);

    printf("\nEND\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    printf("Total conditional statements: %d\n", cond_count);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return;
}

int main() {
    int x,y,j;
    scanf("%d %d", &x, &y);
    test(x,y);
    for (j=0;j<x;j++)
        printf("%d ",arr[j]);
    printf("\n");
    return 0;
}