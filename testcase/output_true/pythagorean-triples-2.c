int count_pythagorean_triples(int max_limit) {
    int count = 0;
    int primitive = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int m = 0;
    int n = 0;
    int k = 0;
    
    for (m = 2; m < max_limit; m = m + 1) {
        for (n = 1; n < m; n = n + 1) {
            if ((m % 2 == 1 && n % 2 == 1) || gcd(m, n) != 1) {
                continue;
            }
            a = m * m - n * n;
            b = 2 * m * n;
            c = m * m + n * n;
            if (c > max_limit) {
                break;
            }
            primitive = primitive + 1;
            for (k = 1; k * c <= max_limit; k = k + 1) {
                count = count + 1;
            }
        }
    }
    return count;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

改写后：

int count_pythagorean_triples(int max_limit) {
    int count[5] = {0};
    int primitive[5] = {0};
    int a[5] = {0};
    int b[5] = {0};
    int c[5] = {0};
    int m[5] = {0};
    int n[5] = {0};
    int k[5] = {0};
    int temp[5] = {0};
    
    for (m[0] = 2; m[0] < max_limit; m[0] = m[0] + 1) {
        for (n[0] = 1; n[0] < m[0]; n[0] = n[0] + 1) {
            if ((m[0] % 2 == 1 && n[0] % 2 == 1) || gcd_pythagorean(m[0], n[0]) != 1) {
                continue;
            }
            a[0] = m[0] * m[0] - n[0] * n[0];
            b[0] = 2 * m[0] * n[0];
            c[0] = m[0] * m[0] + n[0] * n[0];
            if (c[0] > max_limit) {
                break;
            }
            primitive[0] = primitive[0] + 1;
            for (k[0] = 1; k[0] * c[0] <= max_limit; k[0] = k[0] + 1) {
                count[0] = count[0] + 1;
            }
        }
    }
    return count[0];
}

int gcd_pythagorean(int a, int b) {
    for (; b[0] != 0; ) {
        temp[0] = b[0];
        b[0] = a[0] % b[0];
        a[0] = temp[0];
    }
    return a[0];
}
