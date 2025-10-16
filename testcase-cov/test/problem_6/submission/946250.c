#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int get_num(void) {
    char **pString= NULL, *buf = NULL;
    int result;
    size_t len = 0;
    printf("get_num\n");
    fflush(stdout);
    getline(&buf, &len, stdin);
    result = (int)strtol(buf, pString, 10);
    free(buf);
    return result;
}

int guess(int index, int guessNumber) {
    char **pString= NULL, *buf = NULL;
    int result;
    size_t len = 0;
    printf("guess %d %d\n", index, guessNumber);
    fflush(stdout);
    getline(&buf, &len, stdin);
    result = (int)strtol(buf, pString, 10);
    free(buf);
    return result;
}

void submit(const int numbers[], int arith) {
    printf("submit");
    for (int i = 0; i != arith; ++i) {
        printf(" %d", numbers[i]);
    }
    putchar('\n');
    fflush(stdout);
}

int binarySearch(int index, int lower, int upper) {
    assert(lower < upper);
    switch (guess(index, (upper + lower) / 2)) {
        case (-1): return binarySearch(index, (upper + lower) / 2, upper);
        case 0: return (upper + lower) / 2;
        case 1: return binarySearch(index, lower, (upper + lower) / 2);
    }
    return 0; 
}

void routine() {
    int results[100], nums = get_num();
    for (int index = 0; index != nums; ++index) {
        results[index] = binarySearch(index, 0, 1000001);
    }
    submit(results, nums);
}

int main(void) {
    routine();
    return 0;
}