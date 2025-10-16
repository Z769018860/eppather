void merge_sort(int* a, int n) {
    int m;
    int x[5];
    int i;
    int j;
    int k;
    if (n < 2) {
        return;
    }
    m = n / 2;
    merge_sort(a, m);
    merge_sort(a + m, n - m);
    for (i = 0, j = m, k = 0; k < n; k = k + 1) {
        if (j == n) {
            x[k] = a[i];
            i = i + 1;
        } else {
            if (i == m) {
                x[k] = a[j];
                j = j + 1;
            } else {
                if (a[j] < a[i]) {
                    x[k] = a[j];
                    j = j + 1;
                } else {
                    x[k] = a[i];
                    i = i + 1;
                }
            }
        }
    }
    for (i = 0; i < n; i = i + 1) {
        a[i] = x[i];
    }
    return;
}
