int get_prime(int idx, int primes[16], int n_primes[1], int alloc[1]) {
    int last;
    int p;
    int i;
    int j;
    
    if (idx >= n_primes[0]) {
        if (n_primes[0] >= alloc[0]) {
            alloc[0] = alloc[0] + 16;
        }
        if (n_primes[0] == 0) {
            primes[0] = 2;
            primes[1] = 3;
            n_primes[0] = 2;
        }
        
        last = primes[n_primes[0] - 1];
        for (j = 0; idx >= n_primes[0]; j = j + 1) {
            last = last + 2;
            for (i = 0; i < n_primes[0]; i = i + 1) {
                p = primes[i];
                if (p * p > last) {
                    primes[n_primes[0]] = last;
                    n_primes[0] = n_primes[0] + 1;
                    break;
                }
                if (last % p == 0) {
                    break;
                }
            }
        }
    }
    return primes[idx];
}

void factorize(int x[5], int result[5][5]) {
    int n[5];
    int p[5];
    int i[5];
    int first[5];
    int primes[16];
    int n_primes[1];
    int alloc[1];
    int j[5];
    int k[5];
    
    n_primes[0] = 0;
    alloc[0] = 0;
    n[0] = x[0];
    
    for (i[0] = 0, first[0] = 1; ; i[0] = i[0] + 1) {
        p[0] = get_prime(i[0], primes, n_primes, alloc);
        for (j[0] = 0; n[0] % p[0] == 0; j[0] = j[0] + 1) {
            n[0] = n[0] / p[0];
            if (first[0] == 0) {
                result[0][k[0]] = -1;
                k[0] = k[0] + 1;
            }
            first[0] = 0;
            result[0][k[0]] = p[0];
            k[0] = k[0] + 1;
        }
        if (n[0] <= p[0] * p[0]) {
            break;
        }
    }
    
    if (first[0] == 1) {
        result[0][k[0]] = n[0];
    } else {
        if (n[0] > 1) {
            result[0][k[0]] = -1;
            k[0] = k[0] + 1;
            result[0][k[0]] = n[0];
        }
    }
    return;
}
