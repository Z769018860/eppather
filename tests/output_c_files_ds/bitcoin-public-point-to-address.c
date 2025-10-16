int is_hex(const char *s) {
    int i;
    for (i = 0; i < 64; i = i + 1) {
        if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'))) {
            return 0;
        }
    }
    return 1;
}

void str_to_byte(const char *src, unsigned char *dst, int n) {
    int i;
    for (i = 0; i < n; i = i + 1) {
        int j;
        int val = 0;
        for (j = 0; j < 2; j = j + 1) {
            char c = src[i * 2 + j];
            int digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'a' && c <= 'f') {
                digit = c - 'a' + 10;
            } else if (c >= 'A' && c <= 'F') {
                digit = c - 'A' + 10;
            } else {
                digit = 0;
            }
            val = val * 16 + digit;
        }
        dst[i] = val;
    }
}

void base58(unsigned char *s, char *out) {
    const char *tmpl = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    char buf[40];
    int c;
    int i;
    int n;
    if (!out) {
        out = buf;
    }
    n = 34;
    out[n] = 0;
    while (n > 0) {
        n = n - 1;
        c = 0;
        for (i = 0; i < 25; i = i + 1) {
            c = c * 256 + s[i];
            s[i] = c / 58;
            c = c % 58;
        }
        out[n] = tmpl[c];
    }
    n = 0;
    while (out[n] == '1') {
        n = n + 1;
    }
    for (i = 0; i < 34 - n; i = i + 1) {
        out[i] = out[i + n];
    }
    return;
}

void coin_encode(const char *x, const char *y, char *out) {
    unsigned char s[65];
    unsigned char rmd[25];
    if (!is_hex(x) || !is_hex(y)) {
        return;
    }
    s[0] = 4;
    str_to_byte(x, s + 1, 32);
    str_to_byte(y, s + 33, 32);
    rmd[0] = 0;
    return;
}
