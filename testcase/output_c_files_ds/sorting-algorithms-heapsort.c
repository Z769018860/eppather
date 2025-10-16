int max(int *a, int n, int i, int j, int k) {
    int m = i;
    if (j < n) {
        if (a[j] > a[m]) {
            m = j;
        }
    }
    if (k < n) {
        if (a[k] > a[m]) {
            m = k;
        }
    }
    return m;
}

void heapsort(int *a, int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i = i - 1) {
        int current_i = i;
        while (1) {
            int j = max(a, n, current_i, 2 * current_i + 1, 2 * current_i + 2);
            if (j == current_i) {
                break;
            }
            int t = a[current_i];
            a[current_i] = a[j];
            a[j] = t;
            current_i = j;
        }
    }
    for (i = 0; i < n; i = i + 1) {
        int t = a[n - i - 1];
        a[n - i - 1] = a[0];
        a[0] = t;
        int current_i = 0;
        while (1) {
            int j = max(a, n - i - 1, current_i, 2 * current_i + 1, 2 * current_i + 2);
            if (j == current_i) {
                break;
            }
            int t = a[current_i];
            a[current_i] = a[j];
            a[j] = t;
            current_i = j;
        }
    }
    return;
}
