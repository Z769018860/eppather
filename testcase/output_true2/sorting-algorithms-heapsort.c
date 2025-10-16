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

void downheap(int *a, int n, int i) {
    for (;;) {
        int j = max(a, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        i = j;
    }
    return;
}

void heapsort(int *a, int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i = i - 1) {
        downheap(a, n, i);
    }
    for (i = 0; i < n; i = i + 1) {
        int t = a[n - i - 1];
        a[n - i - 1] = a[0];
        a[0] = t;
        downheap(a, n - i - 1, 0);
    }
    return;
}
