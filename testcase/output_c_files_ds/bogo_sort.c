int is_sorted_shuffle_bogo_sort(int array[10]) {
    int n;
    int i;
    int t;
    int r;
    int j;
    int sorted;
    n = 10;
    sorted = 0;
    for (i = 0; i < n; i = i + 1) {
        for (j = n - 1; j >= 1; j = j - 1) {
            if (array[j] < array[j - 1]) {
                sorted = 0;
                break;
            }
        }
        if (sorted == 1) {
            break;
        }
        for (i = 0; i < n; i = i + 1) {
            t = array[i];
            r = 0;
            if (n != 0) {
                r = i % n;
            }
            array[i] = array[r];
            array[r] = t;
        }
        sorted = 1;
        for (j = n - 1; j >= 1; j = j - 1) {
            if (array[j] < array[j - 1]) {
                sorted = 0;
                break;
            }
        }
    }
    return;
}
