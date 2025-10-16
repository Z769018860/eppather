#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int prime[MAXLEN] = {0};

void sieveOfEratosthenes(int n) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int n;\n");
printf("int i;\n");
printf("int p;\n");
printf("double time_taken;\n");
printf("int prime[500000];\n");

    int i,p;
        
    {
      int __first_iter_flag_0 = 1;
    for (i = 0; i < n; i = i + 1) {
    if(__first_iter_flag_0) { 
    printf("i = 0;\n"); 
    __first_iter_flag_0 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < n)\n");
    path_len = path_len + 1;
    
        printf("prime[i] = 1;\n");
        prime[i] = 1;
        mems = mems + 1;
        
    printf("i = i + 1;\n");
}
}

    printf("prime[0] = prime[1] = 0;;\n");
prime[0] = prime[1] = 0;
mems = mems + 2;


    {
      int __first_iter_flag_1 = 1;
    for (p = 2; p * p <= n; p = p + 1) {
    if(__first_iter_flag_1) { 
    printf("p = 2;\n"); 
    __first_iter_flag_1 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(p * p <= n)\n");
    path_len = path_len + 1;
    
        if (prime[p] == 1) {
        cond_count = cond_count + 1;
        printf("@(prime[p] == 1)\n");
        path_len = path_len + 1;
        mems = mems + 1;
        
            {
              int __first_iter_flag_2 = 1;
            for (i = p * p; i <= n; i = i + p) {
            if(__first_iter_flag_2) { 
            printf("i = p * p;\n"); 
            __first_iter_flag_2 = 0; 
            }
            cond_count = cond_count + 1;
            printf("@(i <= n)\n");
            path_len = path_len + 1;
            
                printf("prime[i] = 0;\n");
                prime[i] = 0;
                mems = mems + 1;
                
            printf("i = i + p;\n");
}
}

            ;
        }
        ;
    printf("p = p + 1;\n");
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

int main()
{
    int x,j;
    scanf("%d", &x);
    sieveOfEratosthenes(x);
    for (j=0;j<x;j++)
        printf("%d ",prime[j]);
    printf("\n");
    return 0;
}