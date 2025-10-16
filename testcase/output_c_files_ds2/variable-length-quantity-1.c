void to_seq_from_seq(int x[5], int out[5]) {
    int i;
    int j;
    int temp[5];
    temp[0] = 0;
    for (i = 9; i > 0; i = i - 1) {
        if (x[0] & (127 << (i * 7))) {
            break;
        }
    }
    for (j = 0; j <= i; j = j + 1) {
        out[j] = ((x[0] >> ((i - j) * 7)) & 127) | 128;
    }
    out[i] = out[i] ^ 128;
    for (i = 0; i < 5; i = i + 1) {
        temp[0] = (temp[0] << 7) | (out[i] & 127);
        if (!(out[i] & 128)) {
            break;
        }
    }
    x[0] = temp[0];
    return;
}
