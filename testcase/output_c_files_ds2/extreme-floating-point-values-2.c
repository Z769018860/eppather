int bits(int v[5], int CHARBITS) {
    char s[65];
    int n;
    int i;
    int j;
    unsigned char c[8];
    n = 0;
    for (i = 0; i < 8; i = i + 1) {
        for (j = 32768; j != 0; j = j >> 1) {
            if ((c[i] & j) != 0) {
                s[n] = '1';
            } else {
                s[n] = '.';
            }
            n = n + 1;
        }
        s[n] = ' ';
        n = n + 1;
    }
    s[n - 1] = 0;
    return 0;
}
