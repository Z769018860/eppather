unsigned long long binomial(unsigned long long m, unsigned long long n) {
    unsigned long long r = 1;
    unsigned long long d = m - n;
    if (d > n) {
        n = d;
        d = m - n;
    }
    for (; m > n; m = m - 1) {
        r = r * m;
        for (; d > 1 && (r % d) == 0; d = d - 1) {
            r = r / d;
        }
    }
    return r;
}

unsigned long long catalan(int n) {
    unsigned long long r = 0;
    if (n == 0) {
        r = 1;
    } else {
        unsigned long long sum = 0;
        int i;
        for (i = 0; i < n; i = i + 1) {
            sum = sum + catalan(i) * catalan(n - 1 - i);
        }
        r = sum;
    }
    return r;
}

unsigned long long catalan_frac(int n) {
    unsigned long long r = 1;
    if (n != 0) {
        r = 2 * (2 * n - 1) * catalan_frac(n - 1) / (1 + n);
    }
    return r;
}

unsigned long long catalan_direct(int n) {
    return binomial(2 * n, n) / (1 + n);
}

void combined_catalan() {
    int i;
    unsigned long long c1;
    unsigned long long c2;
    unsigned long long c3;
    for (i = 0; i < 16; i = i + 1) {
        c1 = catalan_direct(i);
        c2 = catalan(i);
        c3 = catalan_frac(i);
    }
    return;
}
