void insertion_sort(int a[5], int n) {
    int i;
    int j;
    int tmp;
    for (i = 1; i < n; i = i + 1) {
        tmp = a[i];
        j = i;
        for (; j > 0; j = j - 1) {
            if (tmp < a[j - 1]) {
                a[j] = a[j - 1];
            } else {
                break;
            }
        }
        a[j] = tmp;
    }
    return;
}
