#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void complex_array_manipulations(int arr[10], int size) {
    int i;
    int j;
    int temp;
    if (arr[0] % 2 == 0) {
        for (i = 0; i < size / 2; i=i+1) {
            temp = arr[i];
            arr[i] = arr[size - i - 1];
            arr[size - i - 1] = temp;
        }
    } else {
        for (i = 0; i < size; i=i+1) {
            arr[i] = arr[i] * arr[i];
        }
    }

    if ((arr[0] + arr[size - 1]) > 100) {
        for (i = 0; i < size; i=i+1) {
            for (j = i + 1; j < size; j=j+1) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    } else {
        int max = arr[0];
        for (i = 1; i < size; i=i+1) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        for (i = 0; i < size; i=i+1) {
            arr[i] = max;
        }
    }

    if (size > 5 && arr[5] % 10 == 0) {
        for (i = 0; i < size / 2; i=i+1) {
            arr[i] = arr[i] * 2;
        }
    }
    return;
}
   
int main()
{
        struct timeval start, end;
    long seconds, useconds;
    double mtime;

    int arr[10];
    int size=2;
    arr[0]=1;
    arr[1]=0;
        gettimeofday(&start, NULL);
    complex_array_manipulations(arr,size);
        gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
    return 0;
}
   
