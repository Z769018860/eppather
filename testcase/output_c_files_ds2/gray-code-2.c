void fmtbool(int n, char buf[6]) {
    char b[6];
    b[5] = 0;
    for (int i = 5; i > 0; i = i - 1) {
        b[i - 1] = 48 + (n & 1);
        n = n >> 1;
    }
    for (int i = 0; i < 5; i = i + 1) {
        buf[i] = b[i];
    }
    return;
}
