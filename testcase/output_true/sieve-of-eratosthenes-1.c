int* eratosthenes(int n, int* c, int sieve[6]) {
    int i;
    int j;
    int m;
    int n1;
    int n2;
    
    if (n < 2) {
        return 0;
    }
    
    *c = n - 1;
    m = 0;
    n1 = n;
    for (i = 0; i < 5; i = i + 1) {
        if (i * i <= n1) {
            m = i;
        }
    }
    
    for (i = 0; i < 6; i = i + 1) {
        sieve[i] = 0;
    }
    sieve[0] = 1;
    sieve[1] = 1;
    
    for (i = 2; i <= m; i = i + 1) {
        if (sieve[i] == 0) {
            n2 = i * i;
            for (j = n2; j <= n; j = j + i) {
                if (sieve[j] == 0) {
                    sieve[j] = 1;
                    *c = *c - 1;
                }
            }
        }
    }
    
    return 0;
}
