int get_prime(int idx, int primes[256], int* n_primes) {
    int last;
    int p;
    int i;
    
    if (idx >= *n_primes) {
        if (*n_primes == 0) {
            primes[0] = 2;
            primes[1] = 3;
            *n_primes = 2;
        }
        
        last = primes[*n_primes - 1];
        while (idx >= *n_primes) {
            last = last + 2;
            for (i = 0; i < *n_primes; i = i + 1) {
                p = primes[i];
                if (p * p > last) {
                    primes[*n_primes] = last;
                    *n_primes = *n_primes + 1;
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

void factorize(int x, int primes[256], int* n_primes) {
    int n;
    int i;
    int first;
    int p;
    
    n = x;
    first = 1;
    
    for (i = 0; ; i = i + 1) {
        p = get_prime(i, primes, n_primes);
        while (n % p == 0) {
            n = n / p;
            first = 0;
        }
        if (n <= p * p) {
            break;
        }
    }
    
    if (n > 1) {
    }
    
    return;
}
