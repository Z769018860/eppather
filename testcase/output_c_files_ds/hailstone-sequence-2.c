int hailstone(int n, int cache[10000000]) {
    int x;
    if (n == 1) {
        return 1;
    }
    if (n < 10000000) {
        if (cache[n] != 0) {
            return cache[n];
        }
    }

    if ((n & 1) != 0) {
        x = 3 * n + 1;
    } else {
        x = n / 2;
    }
    x = 1 + hailstone(x, cache);

    if (n < 10000000) {
        cache[n] = x;
    }
    return x;
}

int find_max_hailstone() {
    int cache[10000000] = {0};
    int i;
    int l;
    int max = 0;
    int mi = 0;
    for (i = 1; i < 10000000; i = i + 1) {
        l = hailstone(i, cache);
        if (l > max) {
            max = l;
            mi = i;
        }
    }
    return mi;
    return;
}
