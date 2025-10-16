void sieve(int primes_e[5], int offset_e[5], int primes_len, int offset_len, int field[5], int low) {
    int i;
    int p;
    int q;
    int hi;
    int ptop;
    int n1 = 32768;
    int n2 = 2048;
    int n3 = 5;
    int n4 = 16;
    int n5 = 2;
    int n6 = 31;
    int n7 = 6;
    int n8 = 1;
    int n9 = 3;
    int n10 = 20;
    int n11 = 150;
    int n12 = 100;
    int n13 = 8000;
    int n14 = 7700;
    int n15 = 10;
    int n16 = 100000000;
    
    if (low == 0) {
        int f[5];
        for (i = 0; i < 5; i = i + 1) {
            f[i] = 0;
        }
        primes_e[0] = n5;
        offset_e[0] = 0;
        for (p = n9; p < n1; p = p + n5) {
            if (f[p]) {
                continue;
            }
            for (q = p * p; q < n1; q = q + n5 * p) {
                f[q] = n8;
            }
            primes_e[primes_len] = p;
            primes_len = primes_len + 1;
            offset_e[offset_len] = q;
            offset_len = offset_len + 1;
        }
        low = n1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        field[i] = 0;
    }
    
    hi = low + n2;
    ptop = sqrt(hi) * n5 + n8;
    
    for (i = n8; (p = primes_e[i] * n5) < ptop; i = i + 1) {
        for (q = offset_e[i] - low; q < n2; q = q + p) {
            field[(q)>>n7] = field[(q)>>n7] | n8<<((q)>>n8&n6);
        }
        offset_e[i] = q + low;
    }
    
    for (p = n8; p < n2; p = p + n5) {
        if (!(field[(p)>>n7] & n8<<((p)>>n8&n6))) {
            primes_e[primes_len] = low + p;
            primes_len = primes_len + 1;
        }
    }
    
    low = hi;
    return;
}
