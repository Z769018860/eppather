void primeFactorization(int n) {
    for (;n % 2 == 0;) {
        n = n / 2;
    }
    int i;
    for (i = 3; i * i <= n; i = i + 2) {
        for (;n % i == 0;) {
            n = n / i;
        }
    }
    if (n > 2) {
    }
    return;
}
