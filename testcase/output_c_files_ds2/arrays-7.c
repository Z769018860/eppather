void func(int* array, int index) {
    *(array + index) = 1;
    array[index] = 5;
    return;
}
