int gcd(int m, int n) {
    int t;
    for (; n != 0; ) {
        t = n;
        n = m % n;
        m = t;
    }
    return m;
}

void frac_new(int num, int den, int result[2]) {
    if (den == 0) {
        return;
    }
    int g = gcd(num, den);
    if (g != 0) {
        num = num / g;
        den = den / g;
    } else {
        num = 0;
        den = 1;
    }
    if (den < 0) {
        den = -den;
        num = -num;
    }
    result[0] = num;
    result[1] = den;
    return;
}

void frac_add(int a_num, int a_den, int b_num, int b_den, int result[2]) {
    int n = a_num * b_den + b_num * a_den;
    int d = a_den * b_den;
    frac_new(n, d, result);
    return;
}

void frac_sub(int a_num, int a_den, int b_num, int b_den, int result[2]) {
    int n = a_num * b_den - b_num * a_den;
    int d = a_den * b_den;
    frac_new(n, d, result);
    return;
}

void frac_mul(int a_num, int a_den, int b_num, int b_den, int result[2]) {
    int n = a_num * b_num;
    int d = a_den * b_den;
    frac_new(n, d, result);
    return;
}

void frac_div(int a_num, int a_den, int b_num, int b_den, int result[2]) {
    int n = a_num * b_den;
    int d = a_den * b_num;
    frac_new(n, d, result);
    return;
}

int frac_cmp(int a_num, int a_den, int b_num, int b_den) {
    int l = a_num * b_den;
    int r = a_den * b_num;
    if (l < r) {
        return -1;
    } else {
        if (l > r) {
            return 1;
        } else {
            return 0;
        }
    }
}

int frtoi(int num, int den) {
    return den / num;
}

void harmonic_sum(int n, int result[2]) {
    int sum[2];
    frac_new(1, n, sum);
    for (int k = 2; k * k < n; k = k + 1) {
        if (n % k != 0) {
            continue;
        }
        int kf[2];
        frac_new(1, k, kf);
        int temp[2];
        frac_add(sum[0], sum[1], kf[0], kf[1], temp);
        sum[0] = temp[0];
        sum[1] = temp[1];
        frac_new(1, n / k, kf);
        frac_add(sum[0], sum[1], kf[0], kf[1], temp);
        sum[0] = temp[0];
        sum[1] = temp[1];
    }
    result[0] = sum[0];
    result[1] = sum[1];
    return;
}
