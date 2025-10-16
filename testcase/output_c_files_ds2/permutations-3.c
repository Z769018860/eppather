int next_lex_perm(int *a, int n) {
    int k, l, t;
    for (k = n - 1; k > 0; k = k - 1) {
        if (a[k - 1] >= a[k]) {
            continue;
        } else {
            break;
        }
    }
    if (k == 0) {
        return 0;
    } else {
        k = k - 1;
    }
    for (l = n - 1; l >= 0; l = l - 1) {
        if (a[l] <= a[k]) {
            continue;
        } else {
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

void boothroyd(int *x, int n, int nn, int callback(int *, int)) {
    int c[5];
    int i[5];
    int t[5];
    c[0] = 0;
    i[0] = 0;
    t[0] = 0;
    while (1) {
        if (n > 2) {
            boothroyd(x, n - 1, nn, callback);
        }
        if (c[0] >= n - 1) {
            return;
        }
        if (n & 1) {
            i[0] = 0;
        } else {
            i[0] = c[0];
        }
        c[0] = c[0] + 1;
        t[0] = x[n - 1];
        x[n - 1] = x[i[0]];
        x[i[0]] = t[0];
        if (callback) {
            callback(x, nn);
        }
    }
    return;
}

void perm3(int *x, int n, int callback(int*, int)) {
    int c[5];
    int d[5];
    int i[5];
    int t[5];
    d[0] = 1;
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    i[0] = 0;
    t[0] = 0;
    if (callback) {
        callback(x, n);
    }
    for (; ; c[d[0]] = c[d[0]] + 1) {
        while (d[0] > 1) {
            d[0] = d[0] - 1;
            c[d[0]] = 0;
        }
        while (c[d[0]] >= d[0]) {
            d[0] = d[0] + 1;
            if (d[0] >= n) {
                goto done;
            }
        }
        if (d[0] & 1) {
            i[0] = c[d[0]];
        } else {
            i[0] = 0;
        }
        t[0] = x[i[0]];
        x[i[0]] = x[d[0]];
        x[d[0]] = t[0];
        if (callback) {
            callback(x, n);
        }
    }
done:
    return;
}
