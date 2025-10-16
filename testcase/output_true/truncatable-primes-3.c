void prime_truncations(int* maxl, int* maxr) {
    int d[4] = {1, 3, 7, 9};
    int n1 = 1000000;
    int n2 = 10;
    int n3 = 6;
    int n4 = 4;
    int n5 = 9;
    int p;
    int i;
    int nn;
    int tens;
    int n;
    
    *maxl = 0;
    *maxr = 0;
    
    for (n = 3; n <= 7; n = n + 4) {
        if (n % 3 == 0) {
            continue;
        }
        p = n3;
        for (; p * p <= n; p = p + n3) {
            if (!(n % (p + 1) && n % (p + 5))) {
                break;
            }
        }
        if (p * p > n) {
            if (n > *maxl) {
                *maxl = n;
            }
            if (n < n1 / n2) {
                for (tens = n2, i = 1; i < n5; i = i + 1) {
                    nn = i * tens + n;
                    if (nn % 3 == 0) {
                        continue;
                    }
                    p = n3;
                    for (; p * p <= nn; p = p + n3) {
                        if (!(nn % (p + 1) && nn % (p + 5))) {
                            break;
                        }
                    }
                    if (p * p > nn) {
                        if (nn > *maxl) {
                            *maxl = nn;
                        }
                    }
                }
            }
        }
    }
    
    for (n = 3; n <= 7; n = n + 2) {
        if (n == 5) {
            continue;
        }
        if (n % 3 == 0) {
            continue;
        }
        p = n3;
        for (; p * p <= n; p = p + n3) {
            if (!(n % (p + 1) && n % (p + 5))) {
                break;
            }
        }
        if (p * p > n) {
            if (n > *maxr) {
                *maxr = n;
            }
            if (n < n1 / n2) {
                for (i = 1; i < n4; i = i + 1) {
                    nn = n * n2 + d[i];
                    if (nn % 3 == 0) {
                        continue;
                    }
                    p = n3;
                    for (; p * p <= nn; p = p + n3) {
                        if (!(nn % (p + 1) && nn % (p + 5))) {
                            break;
                        }
                    }
                    if (p * p > nn) {
                        if (nn > *maxr) {
                            *maxr = nn;
                        }
                    }
                }
            }
        }
    }
    
    return;
}
