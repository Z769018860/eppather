void sieve(int bits[65536], unsigned long primes[7000], unsigned long* n_primes) {
    int i;
    int j;
    for (i = 0; i < 65536; i = i + 1) {
        bits[i] = 1;
    }
    bits[0] = 0;
    bits[1] = 0;
    for (i = 0; i < 256; i = i + 1) {
        if (bits[i] != 0) {
            for (j = i * i; j < 65536; j = j + i) {
                bits[j] = 0;
            }
        }
    }
    j = 0;
    for (i = 0; i < 65536; i = i + 1) {
        if (bits[i] != 0) {
            primes[j] = i;
            j = j + 1;
        }
    }
    *n_primes = j;
    return;
}

int get_prime_factors(unsigned long n, unsigned long primes[7000], unsigned long n_primes, int lst[100][2]) {
    unsigned long i;
    unsigned long e;
    unsigned long p;
    int len = 0;
    for (i = 0; i < n_primes; i = i + 1) {
        p = primes[i];
        if (p * p > n) {
            break;
        }
        e = 0;
        while (n % p == 0) {
            n = n / p;
            e = e + 1;
        }
        if (e != 0) {
            lst[len][0] = p;
            lst[len][1] = e;
            len = len + 1;
        }
    }
    if (n == 1) {
        return len;
    } else {
        lst[len][0] = n;
        lst[len][1] = 1;
        len = len + 1;
        return len;
    }
}

void sort(unsigned long lst[10000], int len) {
    int i;
    int j;
    unsigned long temp;
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (lst[i] > lst[j]) {
                temp = lst[i];
                lst[i] = lst[j];
                lst[j] = temp;
            }
        }
    }
    return;
}

int get_factors(unsigned long n, unsigned long primes[7000], unsigned long n_primes, unsigned long lst[10000]) {
    int f[100][2];
    int n_f;
    int len;
    int len2;
    int i;
    int j;
    int k;
    unsigned long p;
    n_f = get_prime_factors(n, primes, n_primes, f);
    len2 = 1;
    len = 1;
    lst[0] = 1;
    for (i = 0; i < n_f; i = i + 1) {
        p = f[i][0];
        for (j = 0; j < f[i][1]; j = j + 1) {
            for (k = 0; k < len2; k = k + 1) {
                lst[len] = lst[k] * p;
                len = len + 1;
            }
            p = p * f[i][0];
        }
        len2 = len;
    }
    sort(lst, len);
    return len;
}
