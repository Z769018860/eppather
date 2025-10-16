void sieve_get_prime_factors_get_factors(int n1, int n2, int n3, int n4, int lst1[5], int lst2[5], int lst3[5], int lst4[5], int lst5[5], int lst6[5], int lst7[5], int lst8[5], int lst9[5], int lst10[5]) {
    int bits[65536];
    int primes[7000];
    int n_primes;
    int i;
    int j;
    int k;
    int p;
    int e;
    int len;
    int len2;
    int n_f;
    int f_p[100];
    int f_e[100];
    int temp;
    int a;
    int b;

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
    n_primes = j;

    for (i = 0; i < n_primes; i = i + 1) {
        p = primes[i];
        if (p * p > n1) {
            break;
        }
        e = 0;
        while (n1 % p == 0) {
            n1 = n1 / p;
            e = e + 1;
        }
        if (e != 0) {
            f_p[len] = p;
            f_e[len] = e;
            len = len + 1;
        }
    }
    if (n1 != 1) {
        f_p[len] = n1;
        f_e[len] = 1;
        len = len + 1;
    }
    n_f = len;

    len2 = 1;
    lst1[0] = 1;
    for (i = 0; i < n_f; i = i + 1) {
        p = f_p[i];
        for (j = 0; j < f_e[i]; j = j + 1) {
            for (k = 0; k < len2; k = k + 1) {
                lst1[len] = lst1[k] * p;
                len = len + 1;
            }
            p = p * f_p[i];
        }
        len2 = len;
    }

    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            a = lst1[i];
            b = lst1[j];
            if (a > b) {
                temp = lst1[i];
                lst1[i] = lst1[j];
                lst1[j] = temp;
            }
        }
    }

    return;
}
