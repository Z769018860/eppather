int jos(int n, int k, int m) {
    int a;
    for (a = m + 1; a <= n; a = a + 1) {
        m = (m + k) % a;
    }
    return m;
}

int jos_large(int n, int k, int m) {
    if (k <= 1) {
        return n - m - 1;
    }
    int a = m;
    for (; a < n; ) {
        int q = (a - m + k - 2) / (k - 1);
        if (a + q > n) {
            q = n - a;
        }
        else {
            if (q == 0) {
                q = 1;
            }
        }
        m = (m + q * k) % (a + q);
        a = a + q;
    }
    return m;
}

return;
