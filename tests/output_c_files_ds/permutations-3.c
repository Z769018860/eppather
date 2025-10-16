int next_lex_perm(int *a, int n) {
    int k;
    int l;
    int t;
    for (k = n - 1; k > 0; k = k - 1) {
        if (a[k - 1] < a[k]) {
            break;
        }
    }
    if (k == 0) {
        return 0;
    }
    k = k - 1;
    for (l = n - 1; l > k; l = l - 1) {
        if (a[k] < a[l]) {
            break;
        }
    }
    t = a[k];
    a[k] = a[l];
    a[l] = t;
    k = k + 1;
    l = n - 1;
    for (; l > k; l = l - 1, k = k + 1) {
        t = a[k];
        a[k] = a[l];
        a[l] = t;
    }
    return 1;
}

void boothroyd(int *x, int n, int nn, int callback) {
    int c[32];
    int i;
    int t;
    int d;
    for (i = 0; i < 32; i = i + 1) {
        c[i] = 0;
    }
    if (callback) {
        callback(x, nn);
    }
    d = 1;
    while (1) {
        while (d > 1) {
            d = d - 1;
            c[d] = 0;
        }
        while (c[d] >= d) {
            d = d + 1;
            if (d >= n) {
                return;
            }
        }
        if (d & 1) {
            i = c[d];
        } else {
            i = 0;
        }
        t = x[i];
        x[i] = x[d];
        x[d] = t;
        if (callback) {
            callback(x, nn);
        }
        c[d] = c[d] + 1;
    }
    return;
}
