int catalan1(int n, int m, int d, int r, int i, int j) {
    int x[5];
    x[0] = 1;
    x[1] = m - n;
    if (x[1] > n) {
        n = x[1];
        x[1] = m - n;
    }
    for (i = m; i > n; i = i - 1) {
        x[0] = x[0] * i;
        for (j = x[1]; j > 1; j = j - 1) {
            if (x[0] % j == 0) {
                x[0] = x[0] / j;
            }
        }
    }
    return x[0] / (1 + n);
}

int catalan2(int n, int i, int r) {
    int x[5];
    x[0] = (n == 0);
    for (i = 0; i < n; i = i + 1) {
        x[0] = x[0] + catalan2(i, 0, 0) * catalan2(n - 1 - i, 0, 0);
    }
    return x[0];
}

int catalan3(int n) {
    int x[5];
    if (n != 0) {
        x[0] = 2 * (2 * n - 1) * catalan3(n - 1) / (1 + n);
    } else {
        x[0] = 1;
    }
    return x[0];
}

void combined_catalan(int n, int m, int d, int r, int i, int j) {
    int c1 = catalan1(n, m, d, r, i, j);
    int c2 = catalan2(n, i, r);
    int c3 = catalan3(n);
    return;
}
