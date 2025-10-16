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
    int d[5];
    d[0] = 5;
    for (; d[0] * d[0] <= n; ) {
        if (n % d[0] == 0) {
            return 0;
        }
        d[0] = d[0] + 2;
        if (n % d[0] == 0) {
            return 0;
        }
        d[0] = d[0] + 4;
    }
    return 1;
}

void combinedFunction(int q) {
    int i[5];
    int d[5];
    int p[5];
    int r[5];
    if (!isPrime(q)) {
        return;
    }
    r[0] = q;
    for (; r[0] > 0; ) {
        r[0] = r[0] << 1;
    }
    d[0] = 2 * q + 1;
    for (; ; ) {
        p[0] = r[0];
        i[0] = 1;
        for (; p[0]; p[0] = p[0] << 1) {
            i[0] = (i[0] * i[0]) % d[0];
            if (p[0] < 0) {
                i[0] = i[0] * 2;
            }
            if (i[0] > d[0]) {
                i[0] = i[0] - d[0];
            }
        }
        if (i[0] != 1) {
            d[0] = d[0] + 2 * q;
        } else {
            break;
        }
    }
    return;
}
