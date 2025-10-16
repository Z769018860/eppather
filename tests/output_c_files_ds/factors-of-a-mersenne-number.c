int isPrime(int n) {
    if (n % 2 == 0) {
        if (n == 2) {
            return 1;
        } else {
            return 0;
        }
    }
    if (n % 3 == 0) {
        if (n == 3) {
            return 1;
        } else {
            return 0;
        }
    }
    int d = 5;
    for (; d * d <= n; ) {
        if (n % d == 0) {
            return 0;
        }
        d = d + 2;
        if (n % d == 0) {
            return 0;
        }
        d = d + 4;
    }
    return 1;
}

void mainFunc() {
    int i;
    int d;
    int p;
    int r;
    int q = 929;
    if (isPrime(q) == 0) {
        return;
    }
    r = q;
    for (; r > 0; ) {
        r = r << 1;
    }
    d = 2 * q + 1;
    for (; ; ) {
        p = r;
        i = 1;
        for (; p; p = p << 1) {
            i = (i * i) % d;
            if (p < 0) {
                i = i * 2;
            }
            if (i > d) {
                i = i - d;
            }
        }
        if (i != 1) {
            d = d + 2 * q;
        } else {
            break;
        }
    }
    return;
}
