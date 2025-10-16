int is_prime(int n) {
    int p;
    if (n < 2) {
        return 0;
    }
    if ((n & 1) == 0) {
        if (n == 2) {
            return 1;
        } else {
            return 0;
        }
    }
    for (p = 3; p <= n / p; p = p + 2) {
        if ((n % p) == 0) {
            return 0;
        }
    }
    return 1;
}
