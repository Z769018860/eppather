int is_sorted(int* a, int n) {
    for (n = n - 1; n >= 1; n = n - 1) {
        if (a[n] < a[n - 1]) {
            return 0;
        }
    }
    return 1;
}

void shuffle(int* a, int n) {
    int i;
    int t;
    int r;
    for (i = 0; i < n; i = i + 1) {
        t = a[i];
        r = 0;
        a[i] = a[r];
        a[r] = t;
    }
}

void bogosort(int* a, int n) {
    for (; is_sorted(a, n) == 0; ) {
        shuffle(a, n);
    }
    return;
}
