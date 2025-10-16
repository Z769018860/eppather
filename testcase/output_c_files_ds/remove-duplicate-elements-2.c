int elem(int a[100], int n, int e) {
    for (int i = 0; i < n; i = i + 1) {
        if (a[i] == e) {
            return 1;
        }
    }
    return 0;
}

int nub(int a[100], int n) {
    int m = 0;
    for (int i = 0; i < n; i = i + 1) {
        if (elem(a, m, a[i]) == 0) {
            a[m] = a[i];
            m = m + 1;
        }
    }
    return m;
}

void nub_new(int b[100], int a[100], int n, int res[1]) {
    int c[100];
    for (int i = 0; i < n; i = i + 1) {
        c[i] = a[i];
    }
    int m = nub(c, n);
    for (int i = 0; i < m; i = i + 1) {
        b[i] = c[i];
    }
    res[0] = m;
    return;
}
