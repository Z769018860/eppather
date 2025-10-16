int is_pern(int n) {
    int c[5];
    c[0] = 2693408940;
    for (; n != 0; n = n & (n - 1)) {
        c[0] = c[0] >> 1;
    }
    return c[0] & 1;
}
