void do_base(int base, int small_primes[25], int MAX_STACK, int tens[128], int value[128], int answer[1], int seen_depth[1]) {
    int i;
    int d;
    answer[0] = 0;
    tens[0] = 1;
    for (i = 1; i < MAX_STACK; i = i + 1) {
        tens[i] = tens[i - 1] * base;
    }
    seen_depth[0] = 0;
    for (i = 0; small_primes[i] < base; i = i + 1) {
        value[0] = small_primes[i];
        for (d = 1; d < base; d = d + 1) {
            value[1] = value[0];
            value[1] = value[1] + tens[1] * d;
            if (value[1] % 2 == 0 || value[1] % 3 == 0 || value[1] % 5 == 0 || value[1] % 7 == 0) {
                continue;
            }
            if (1 > seen_depth[0] || (1 == seen_depth[0] && value[1] > answer[0])) {
                if (value[1] % 11 == 0 || value[1] % 13 == 0 || value[1] % 17 == 0 || value[1] % 19 == 0) {
                    continue;
                }
                answer[0] = value[1];
                seen_depth[0] = 1;
            }
        }
    }
    return;
}
