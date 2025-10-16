int kaprekars(int base, long long top, long long out[1000], int max_cnt) {
    long long f[64];
    long long pb;
    int len;
    int cnt = 0;
    long long a;
    int i;
    long long x;
    long long b0;
    long long t;
    long long q;
    long long x0;
    long long x1;
    int j;
    long long p;
    long long inc;
    int k;
    long long n;

    out[cnt] = 1;
    cnt = cnt + 1;

    for (pb = base; pb <= top * top / base; pb = pb * base) {
        n = pb - 1;
        i = 0;
        p = 2;
        while (1) {
            if (n % p == 0) {
                f[i] = 1;
                while (n % p == 0) {
                    f[i] = f[i] * p;
                    n = n / p;
                }
                i = i + 1;
            }
            if (n % p != 0) {
                break;
            }
        }
        p = 3;
        while (1) {
            if (n % p == 0) {
                f[i] = 1;
                while (n % p == 0) {
                    f[i] = f[i] * p;
                    n = n / p;
                }
                i = i + 1;
            }
            if (n % p != 0) {
                break;
            }
        }
        p = 5;
        inc = 4;
        while (p * p <= n) {
            if (n % p == 0) {
                f[i] = 1;
                while (n % p == 0) {
                    f[i] = f[i] * p;
                    n = n / p;
                }
                i = i + 1;
            }
            if (n % p != 0) {
                inc = 6 - inc;
                p = p + inc;
            }
        }
        if (n > 1) {
            f[i] = 1;
            while (n % p == 0) {
                f[i] = f[i] * p;
                n = n / p;
            }
            i = i + 1;
        }
        len = i;

        if (f[len - 1] <= top) {
            for (k = 0; k < (1 << len); k = k + 1) {
                a = 1;
                for (j = 0; j < len; j = j + 1) {
                    if (k & (1 << j)) {
                        a = a * f[j];
                    }
                }
                b0 = (pb - 1) / a;
                x1 = 1;
                if (b0 != 1) {
                    a = a % b0;
                    x0 = 0;
                    x1 = 1;
                    while (a > 1) {
                        q = a / b0;
                        t = b0;
                        b0 = a % b0;
                        a = t;
                        t = x0;
                        x0 = x1 - q * x0;
                        x1 = t;
                    }
                    if (x1 < 0) {
                        x1 = x1 + ((pb - 1) / a);
                    }
                }
                x = a * x1;
                if (x > 1 && x < top) {
                    out[cnt] = x;
                    cnt = cnt + 1;
                    if (cnt >= max_cnt) {
                        return cnt;
                    }
                }
            }
        }
    }
    return cnt;
}
