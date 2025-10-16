int is_prime(int n[5]) {
    int factor[5];
    int has_factor[5] = {0};
    int out[5] = {1};
    int i[5] = {0};
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        factor[0] = i[0] + 2;
        if (n[0] % factor[0] == 0) {
            if (has_factor[0]) {
                out[0] = 0;
                return out[0];
            }
            has_factor[0] = 1;
        }
    }
    return out[0];
}

int is_prime_cached(int n[5]) {
    int half_n[5];
    int upb_cache[5] = {32};
    int cached[5] = {0};
    int cache[5] = {0};
    int out[5];
    half_n[0] = n[0] / 2 - 2;
    if (half_n[0] <= upb_cache[0]) {
        if ((cached[0] >> half_n[0]) & 1) {
            return (cache[0] >> half_n[0]) & 1;
        } else {
            out[0] = is_prime(n);
            cache[0] = cache[0] | (out[0] << half_n[0]);
            cached[0] = cached[0] | (1 << half_n[0]);
            return out[0];
        }
    } else {
        return is_prime(n);
    }
}

void primes() {
    int n[5] = {3};
    int max_lint[5] = {2147483647};
    if (is_prime_cached(n) == 1) {
        n[0] = n[0] + 2;
    }
    for (n[0] = 3; n[0] < max_lint[0] - 2; n[0] = n[0] + 2) {
        if (is_prime_cached(n) == 1) {
            n[0] = n[0] + 2;
        }
    }
    return;
}

void decompose(int in_n[5]) {
    int n[5];
    int p[5];
    n[0] = in_n[0];
    for (p[0] = 2; p[0] * p[0] <= n[0]; p[0] = p[0] + 1) {
        if (is_prime_cached(p) == 1) {
            while (n[0] % p[0] == 0) {
                n[0] = n[0] / p[0];
            }
        }
    }
    if (n[0] > 1) {
        p[0] = n[0];
    }
    return;
}
