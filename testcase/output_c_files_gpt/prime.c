void primeFactorization(int n) {
    int i = 3;
    for (; n % 2 == 0; n = n / 2) {
        /* Removed printf statement */
    }
    for (; i * i <= n; i = i + 2) {
        for (; n % i == 0; n = n / i) {
            /* Removed printf statement */
        }
    }
    if (n > 2) {
        /* Removed printf statement */
    }
    return;
}
