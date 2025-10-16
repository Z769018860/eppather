int c[100];

void coef_is_prime_show() {
    int i;
    int j;
    int n;
    int k;
    for (n = 0; n < 10; n = n + 1) {
        if (n < 0 || n > 63) {
            return;
        }
        c[0] = 1;
        for (i = 0; i < n; i = i + 1) {
            c[0] = -c[0];
            for (j = i; j > 0; j = j - 1) {
                c[j] = c[j - 1] - c[j];
            }
            c[1 + i] = 1;
        }
        for (k = n; k >= 0; k = k - 1) {
        }
    }
    for (n = 1; n <= 63; n = n + 1) {
        if (n < 0 || n > 63) {
            return;
        }
        c[0] = 1;
        for (i = 0; i < n; i = i + 1) {
            c[0] = -c[0];
            for (j = i; j > 0; j = j - 1) {
                c[j] = c[j - 1] - c[j];
            }
            c[1 + i] = 1;
        }
        c[0] = c[0] + 1;
        c[n] = c[n] - 1;
        i = n;
        while (i >= 0) {
            if (c[i] % n != 0) {
                break;
            }
            i = i - 1;
        }
    }
    return;
}
