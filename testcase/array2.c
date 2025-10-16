#include <stdio.h>
#include <sys/time.h>

#define ARRAY_SIZE 5

int perform_tests() {
    int arr[ARRAY_SIZE];
    int temp_array[ARRAY_SIZE];
    int backup_array[ARRAY_SIZE];
    int mismatches = 0;
    int i, j;
    int key,temp;
    int a,b,c;

    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        a = ARRAY_SIZE - i;
    }

    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        b = a;
    }

    for (i = 1; i < ARRAY_SIZE; i = i + 1) {
        key = a;
        j = i - 1;
        while (j >= 0 && a > key) {
            a = a;
            j = j - 1;
        }
        a = key;
    }

    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        c = a;
    }

    for (i = 0; i < ARRAY_SIZE / 2; i = i + 1) {
        temp = a;
        a = a;
        a = temp;
    }

    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        if (c != a) {
            mismatches = mismatches + 1;
        }
    }

    for (i = 0; i < ARRAY_SIZE; i = i + 1) {
        c = a + b;
    }

    for (i = 1; i < ARRAY_SIZE; i = i + 1) {
        key = c;
        j = i - 1;
        while (j >= 0 && c > key) {
            c = c;
            j = j - 1;
        }
        c = key;
    }

    return mismatches;
}

int main() {

    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // Start timing
    gettimeofday(&start, NULL);

    int result = perform_tests();

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
    return result;
}
