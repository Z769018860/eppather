void encode(const char *s, char *enc, char *tb) {
    int i;
    int j;
    int k;
    int temp;
    int enc_len[5] = {0};
    for (i = 0; s[i] != 0; i = i + 1) {
        if (tb[s[i]] != 0) {
            enc[enc_len[0]] = tb[s[i]];
            enc_len[0] = enc_len[0] + 1;
        } else {
            enc[enc_len[0]] = 37;
            enc_len[0] = enc_len[0] + 1;
            temp = s[i];
            for (j = 0; j < 2; j = j + 1) {
                k = (temp >> 4) & 15;
                if (k < 10) {
                    enc[enc_len[0]] = k + 48;
                } else {
                    enc[enc_len[0]] = k + 55;
                }
                enc_len[0] = enc_len[0] + 1;
                temp = temp << 4;
            }
        }
    }
    enc[enc_len[0]] = 0;
    return;
}
