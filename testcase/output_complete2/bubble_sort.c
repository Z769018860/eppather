void bubble_sort(int* array, int n) {
    int i;
    int j;
    int tmp;
    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n - 1; j = j + 1) {
            if (array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    return;
}
