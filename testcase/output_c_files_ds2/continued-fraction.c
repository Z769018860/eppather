int calc(int f_a, int f_b, int expansions) {
    int a[5];
    int b[5];
    int r[5];
    a[0] = 0;
    b[0] = 0;
    r[0] = 0;
    
    int i;
    for (i = expansions; i > 0; i = i - 1) {
        a[0] = f_a;
        b[0] = f_b;
        r[0] = b[0] / (a[0] + r[0]);
    }
    a[0] = f_a;
    
    return a[0] + r[0];
}

int sqrt2_a(int n) {
    if (n != 0) {
        return 2;
    } else {
        return 1;
    }
}

int sqrt2_b(int n) {
    return 1;
}

int napier_a(int n) {
    if (n != 0) {
        return n;
    } else {
        return 2;
    }
}

int napier_b(int n) {
    if (n > 1) {
        return n - 1;
    } else {
        return 1;
    }
}

int pi_a(int n) {
    if (n != 0) {
        return 6;
    } else {
        return 3;
    }
}

int pi_b(int n) {
    int c[5];
    c[0] = 2 * n - 1;
    return c[0] * c[0];
}

void main() {
    int sqrt2[5];
    int napier[5];
    int pi[5];
    
    sqrt2[0] = calc(sqrt2_a(0), sqrt2_b(0), 5);
    napier[0] = calc(napier_a(0), napier_b(0), 5);
    pi[0] = calc(pi_a(0), pi_b(0), 5);
    
    return;
}
