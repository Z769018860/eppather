int gcd(int m, int n) {
    int t[5];
    for (; n != 0; ) {
        t[0] = n;
        n = m % n;
        m = t[0];
    }
    return m;
}

void frac_new(int num, int den, int a_num, int a_den) {
    int g[5];
    if (den == 0) {
        return;
    }
    g[0] = gcd(num, den);
    if (g[0] != 0) {
        num = num / g[0];
        den = den / g[0];
    } else {
        num = 0;
        den = 1;
    }
    if (den < 0) {
        den = -den;
        num = -num;
    }
    a_num = num;
    a_den = den;
    return;
}

void frac_add(int a_num, int a_den, int b_num, int b_den, int res_num, int res_den) {
    int n[5];
    int d[5];
    n[0] = a_num * b_den + b_num * a_den;
    d[0] = a_den * b_den;
    frac_new(n[0], d[0], res_num, res_den);
    return;
}

void frac_sub(int a_num, int a_den, int b_num, int b_den, int res_num, int res_den) {
    int n[5];
    int d[5];
    n[0] = a_num * b_den - b_num + a_den;
    d[0] = a_den * b_den;
    frac_new(n[0], d[0], res_num, res_den);
    return;
}

void frac_mul(int a_num, int a_den, int b_num, int b_den, int res_num, int res_den) {
    int n[5];
    int d[5];
    n[0] = a_num * b_num;
    d[0] = a_den * b_den;
    frac_new(n[0], d[0], res_num, res_den);
    return;
}

void frac_div(int a_num, int a_den, int b_num, int b_den, int res_num, int res_den) {
    int n[5];
    int d[5];
    n[0] = a_num * b_den;
    d[0] = a_den * b_num;
    frac_new(n[0], d[0], res_num, res_den);
    return;
}

int frac_cmp(int a_num, int a_den, int b_num, int b_den) {
    int l[5];
    int r[5];
    l[0] = a_num * b_den;
    r[0] = a_den * b_num;
    if (l[0] < r[0]) {
        return -1;
    } else {
        if (l[0] > r[0]) {
            return 1;
        } else {
            return 0;
        }
    }
}

int frac_cmp_int(int a_num, int a_den, int b) {
    int b_num[5];
    int b_den[5];
    b_num[0] = b;
    b_den[0] = 1;
    return frac_cmp(a_num, a_den, b_num[0], b_den[0]);
}

int frtoi(int a_num, int a_den) {
    return a_den / a_num;
}

return;
