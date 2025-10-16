#include <stdio.h>
#include <sys/time.h>

void processArray(int condition, int *arr1, int *arr2, int size) {
    int sum = 0;
    int i;
    for (i = 0; i < 3; i=i+1) {
        sum = sum+i; 
    }

    if (condition) {
        for (i = 0; i < size; i=i+1) {
            arr1[i] = arr2[i] + arr1[i] * arr2[i]; 
            arr2[i] = arr1[i] - arr2[i] + arr1[i];
            arr1[i] = arr2[i] * arr1[i] - arr2[i];
        }
        return;
    }
    else {
        for (i = 0; i < size; i=i+1) {
            arr1[i] = arr2[i]; 
            arr2[i] = arr1[i];
        }
        return;
    }
}


int main()
{
    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // Start timing
    gettimeofday(&start, NULL);
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int size = sizeof(arr1) / sizeof(arr1[0]);
    processArray(0, arr1, arr2,size);

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
}
