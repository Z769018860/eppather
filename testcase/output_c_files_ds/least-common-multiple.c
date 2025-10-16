int func(int m, int n) {
    int tmp;
    int gcd_m;
    int gcd_n;
    gcd_m = m;
    gcd_n = n;
    for (; gcd_m != 0; ) {
        tmp = gcd_m;
        gcd_m = gcd_n % gcd_m;
        gcd_n = tmp;
    }
    return m / gcd_n * n;
    return;
}
