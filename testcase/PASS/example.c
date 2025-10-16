#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

void test(int n,int mode) {
    clock_t start, end;
    start = clock();
    int a = 0, b = 0;
    int i;

    for(i=0; i<n; i++) {                
        if(mode>0){
            arr[i] = i * 2+arr[i];              
            mode=mode-1;                  
        } else {
            b = i * 3+b;                  
            mode=mode-1;                       
        }
    }
    printf("END\n");
    printf("%d %d",a,b);

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