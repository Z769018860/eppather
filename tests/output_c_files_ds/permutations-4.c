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

void perm1(int *x, int n) {
    do {
    } while (next_lex_perm(x, n));
    return;
}

void boothroyd(int *x, int n, int nn) {
    int c = 0;
    int i;
    int t;
    while (1) {
        if (n > 2) {
            boothroyd(x, n - 1, nn);
        }
        if (c >= n - 1) {
            return;
        }
        if (n & 1) {
            i = 0;
        } else {
            i = c;
        }
        c = c + 1;
        t = x[n - 1];
        x[n - 1] = x[i];
        x[i] = t;
    }
    return;
}

void perm2(int *x, int n) {
    boothroyd(x, n, n);
    return;
}

void perm3(int *x, int n) {
    int c[32];
    int d;
    int i;
    int t;
    for (d = 0; d < 32; d = d + 1) {
        c[d] = 0;
    }
    for (d = 1; ; d = d + 1) {
        c[d] = c[d] + 1;
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
    }
    return;
}
