#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};
int mems = 0;
int path_len = 0;

void test(int n, int mode) {
    clock_t start, end;
    start = clock();
    
    int a = 0, b = 0;
    int i,j;
    
    printf("Path: \n");
    
    for(i = 0; i < n; i = i + 1) {  
        printf("@(i < n)\n");
        path_len = path_len + 1;      
        
        if(mode > 0) {
            printf("@(mode > 0)\n");
            path_len = path_len + 1;
            
            printf("arr[i] = i * 2; \n");
            arr[i] = i * 2+arr[i];
            mems = mems + 2;
            
            printf("mode = mode - 1; \n");
            mode = mode - 1;
        } else {
            printf("@(mode <= 0) \n");
            path_len = path_len + 1;
            
            printf("b = i * 3; \n");
            b = i * 3+b;
            
            printf("mode = mode - 1; \n");
            mode = mode - 1;
        }
    }

    printf("END\n");
    printf("%d %d",a,b);
    for (j=0;j<n;j++)
        printf("%d ",arr[j]);
    printf("\n");
    printf("\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    
    return;
}

int main() {
    int x, y;
    int j;
    scanf("%d %d", &x, &y);
    test(x, y);
    return 0;
}
