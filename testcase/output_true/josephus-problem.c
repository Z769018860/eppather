int jos(int n, int k, int m) {
    int a;
    for (a = m + 1; a <= n; a = a + 1) {
        m = (m + k) % a;
    }
    return m;
}

int jos_large(int n, int k, int m) {
    int a[5];
    int q[5];
    a[0] = m;
    if (k <= 1) {
        return n - m - 1;
    }
    for (; a[0] < n; ) {
        q[0] = (a[0] - m + k - 2) / (k - 1);
        if (a[0] + q[0] > n) {
            q[0] = n - a[0];
        } else {
            if (q[0] == 0) {
                q[0] = 1;
            }
        }
        m = (m + q[0] * k) % (a[0] + q[0]);
        a[0] = a[0] + q[0];
    }
    return m;
}

void combined_jos(int n, int k, int m, int* result1, int* result2) {
    *result1 = jos(n, k, m);
    *result2 = jos_large(n, k, m);
    return;
}
