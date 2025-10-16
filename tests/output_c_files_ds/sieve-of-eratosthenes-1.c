int* eratosthenes(int n, int* c) {
    int sieve[1000];
    int i;
    int j;
    int m;
    if (n < 2) {
        return 0;
    }
    *c = n - 1;
    m = 0;
    while (m * m <= n) {
        m = m + 1;
    }
    m = m - 1;
    for (i = 0; i <= n; i = i + 1) {
        sieve[i] = 0;
    }
    sieve[0] = 1;
    sieve[1] = 1;
    for (i = 2; i <= m; i = i + 1) {
        if (sieve[i] == 0) {
            for (j = i * i; j <= n; j = j + i) {
                if (sieve[j] == 0) {
                    sieve[j] = 1;
                    *c = *c - 1;
                }
            }
        }
    }
    return sieve;
}
