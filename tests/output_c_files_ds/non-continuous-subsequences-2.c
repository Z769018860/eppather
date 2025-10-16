void binprint(unsigned int n, unsigned int m) {
    char c[32];
    int i;
    i = 0;
    for (; m > 0; m = m >> 1) {
        if (n & m) {
            c[i] = '#';
        } else {
            c[i] = '-';
        }
        i = i + 1;
    }
    c[i] = '\0';
    return;
}
