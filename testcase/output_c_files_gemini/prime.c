void primeFactorization(int n) {
    int factors[100];
    int factor_index;
    int i;

    factor_index = 0;

    for (; (n % 2) == 0; ) {
        factors[factor_index] = 2;
        factor_index = factor_index + 1;
        n = n / 2;
    }

    for (i = 3; (i * i) <= n; i = i + 2) {
        for (; (n % i) == 0; ) {
            factors[factor_index] = i;
            factor_index = factor_index + 1;
            n = n / i;
        }
    }

    if (n > 2) {
        factors[factor_index] = n;
        factor_index = factor_index + 1;
    }

    return;
}
