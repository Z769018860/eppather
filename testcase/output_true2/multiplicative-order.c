int mpow(int a, int p, int m) {
    int r[5];
    r[0] = 1;
    for (; p; p = p >> 1) {
        if ((1 & p)) {
            r[0] = r[0] * a % m;
        }
        a = a * a % m;
    }
    return r[0];
}

int ipow(int a, int p) {
    int r[5];
    r[0] = 1;
    for (; p; p = p >> 1) {
        if ((1 & p)) {
            r[0] = r[0] * a;
        }
        a = a * a;
    }
    return r[0];
}

int gcd(int m, int n) {
    int t[5];
    for (; m; ) {
        t[0] = m;
        m = n % m;
        n = t[0];
    }
    return n;
}

int lcm(int m, int n) {
    int g[5];
    g[0] = gcd(m, n);
    return m / g[0] * n;
}

int multi_order_p(int a, int p, int e) {
    int fac[5];
    int m[5];
    int t[5];
    int i;
    int len[5];
    m[0] = ipow(p, e);
    t[0] = m[0] / p * (p - 1);
    len[0] = 5;
    for (i = 0; i < 5; i = i + 1) {
        fac[i] = 0;
    }
    for (i = 0; i < len[0]; i = i + 1) {
        if (mpow(a, fac[i], m[0]) == 1) {
            return fac[i];
        }
    }
    return 0;
}

int multi_order(int a, int m) {
    int pf_p[5];
    int pf_e[5];
    int i;
    int len[5];
    int res[5];
    res[0] = 1;
    len[0] = 5;
    for (i = 0; i < 5; i = i + 1) {
        pf_p[i] = 0;
        pf_e[i] = 0;
    }
    for (i = 0; i < len[0]; i = i + 1) {
        res[0] = lcm(res[0], multi_order_p(a, pf_p[i], pf_e[i]));
    }
    return res[0];
}
