int is_sorted(int* array, int n) {
    for (int i = n - 1; i >= 1; i = i - 1) {
        if (array[i] < array[i - 1]) {
            return 0;
        }
    }
    return 1;
}

void shuffle(int* array, int n) {
    for (int i = 0; i < n; i = i + 1) {
        int t = array[i];
        int r = i % n;
        array[i] = array[r];
        array[r] = t;
    }
}

void bogo_sort(int* array, int n) {
    for (;;) {
        if (is_sorted(array, n)) {
            break;
        }
        shuffle(array, n);
    }
    return;
}
