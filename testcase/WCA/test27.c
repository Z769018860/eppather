#include <stdio.h>
#include <sys/time.h>

void array_operations(int arr[10], int size) {
    int i, j;
    int sum = 0;
    int product = 1;
    int threshold = 0;
    
    for (i = 0; i < size; i=i+1) {
        sum = sum + i;
        product = product * i;
    }
    
    if (sum > threshold) {
        arr[0] = arr[0] - 1;
        arr[1] = arr[0] + 1;
        j=j+1;
        j=j+1;
        j=j+1;
        return;
    } else {
        arr[0] = arr[0] - 1; arr[1] = arr[0] + 1;
        arr[2] = arr[2] / 2; arr[3] = arr[3] * 2;
        arr[4] = arr[4] / arr[0]; arr[1] = arr[1] - arr[3];
    }
}


int main()
{
    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // Start timing
    gettimeofday(&start, NULL);

    int a[10] = {2, 0, 4, 1, 8, 0, 0, 0, 0, 0};
    int b = 3;
    array_operations(a, b);

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
}
