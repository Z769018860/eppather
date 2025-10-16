void to_seq_from_seq(unsigned long long x, unsigned char out[10], unsigned long long* result) {
    int i;
    int j;
    for (i = 9; i > 0; i = i - 1) {
        if (x & ((unsigned long long)127 << (i * 7))) {
            break;
        }
    }
    for (j = 0; j <= i; j = j + 1) {
        out[j] = ((x >> ((i - j) * 7)) & 127) | 128;
    }
    out[i] = out[i] ^ 128;

    unsigned long long r = 0;
    int k = 0;
    for (;;) {
        r = (r << 7) | (unsigned long long)(out[k] & 127);
        if (!(out[k] & 128)) {
            break;
        }
        k = k + 1;
    }
    *result = r;
    return;
}
