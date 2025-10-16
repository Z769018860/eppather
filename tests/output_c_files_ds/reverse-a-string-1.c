int is_comb(int c) {
    if (c >= 0x300 && c <= 0x36f) {
        return 1;
    }
    if (c >= 0x1dc0 && c <= 0x1dff) {
        return 1;
    }
    if (c >= 0x20d0 && c <= 0x20ff) {
        return 1;
    }
    if (c >= 0xfe20 && c <= 0xfe2f) {
        return 1;
    }
    return 0;
}

void ws_reverse(int* out, const int* u, int len) {
    int i;
    int j;
    int temp_len;
    temp_len = len;
    j = 0;
    for (; temp_len > 0; ) {
        i = temp_len - 1;
        for (; i > 0 && is_comb(u[i]); i = i - 1) {
        }
        for (; i < temp_len; i = i + 1) {
            out[j] = u[i];
            j = j + 1;
        }
        temp_len = temp_len - (temp_len - i);
    }
    out[len] = 0;
    return;
}
