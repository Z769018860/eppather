unsigned long binomial(unsigned long n, unsigned long k) {
    unsigned long d[5];
    unsigned long g[5];
    unsigned long r[5];
    unsigned long nr[5];
    unsigned long dr[5];
    unsigned long t[5];
    r[0] = 1;
    if (k == 0) {
        return 1;
    }
    if (k == 1) {
        return n;
    }
    if (k >= n) {
        return (k == n);
    }
    if (k > n/2) {
        k = n-k;
    }
    for (d[0] = 1; d[0] <= k; d[0] = d[0] + 1) {
        if (r[0] >= 18446744073709551615UL/n) {
            g[0] = n;
            t[0] = d[0];
            if (t[0] < g[0]) {
                t[1] = g[0];
                g[0] = t[0];
                t[0] = t[1];
            }
            for (t[2] = t[0]; t[2] > 0; t[2] = t[3]) {
                t[3] = t[2];
                t[2] = g[0] % t[2];
                g[0] = t[3];
            }
            nr[0] = n/g[0];
            dr[0] = d[0]/g[0];
            g[1] = r[0];
            t[4] = dr[0];
            if (t[4] < g[1]) {
                t[1] = g[1];
                g[1] = t[4];
                t[4] = t[1];
            }
            for (t[2] = t[4]; t[2] > 0; t[2] = t[3]) {
                t[3] = t[2];
                t[2] = g[1] % t[2];
                g[1] = t[3];
            }
            r[0] = r[0]/g[1];
            dr[0] = dr[0]/g[1];
            if (r[0] >= 18446744073709551615UL/nr[0]) {
                return 0;
            }
            r[0] = r[0] * nr[0];
            r[0] = r[0] / dr[0];
            n = n - 1;
        } else {
            r[0] = r[0] * n;
            r[0] = r[0] / d[0];
            n = n - 1;
        }
    }
    return r[0];
}
