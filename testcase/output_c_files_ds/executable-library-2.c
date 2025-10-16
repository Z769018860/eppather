int hailstone(int n, int seq[100]) {
    int len = 0;
    for (;;) {
        if (seq) {
            seq[len] = n;
        }
        len = len + 1;
        if (n == 1) {
            break;
        }
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
    }
    return len;
}
