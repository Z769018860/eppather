int lzw_encode_decode(int in[5], int max_bits, int mode) {
    int d_enc[512][256];
    int d_dec[512][3];
    int out[5] = {0};
    int len = in[0];
    int bits = 9;
    int next_shift = 512;
    int code = 0;
    int c = 0;
    int nc = 0;
    int next_code = 258;
    int out_len = 0;
    int o_bits = 0;
    int tmp = 0;
    int n_bits = 0;
    int j = 0;
    int t = 0;

    if (max_bits > 15) {
        max_bits = 15;
    }
    if (max_bits < 9) {
        max_bits = 12;
    }

    for (int i = 0; i < 512; i = i + 1) {
        for (int k = 0; k < 256; k = k + 1) {
            d_enc[i][k] = 0;
        }
    }

    for (int i = 0; i < 512; i = i + 1) {
        d_dec[i][0] = 0;
        d_dec[i][1] = 0;
        d_dec[i][2] = 0;
    }

    if (mode == 0) {
        code = in[1];
        for (int i = 1; i < len; i = i + 1) {
            c = in[i + 1];
            nc = d_enc[code][c];
            if (nc != 0) {
                code = nc;
            } else {
                tmp = (tmp << bits) | code;
                o_bits = o_bits + bits;
                if (o_bits >= 8) {
                    o_bits = o_bits - 8;
                    out[out_len] = tmp >> o_bits;
                    out_len = out_len + 1;
                    tmp = tmp & ((1 << o_bits) - 1);
                }
                d_enc[code][c] = next_code;
                next_code = next_code + 1;
                code = c;
            }

            if (next_code == next_shift) {
                if (bits + 1 > max_bits) {
                    tmp = (tmp << bits) | 256;
                    o_bits = o_bits + bits;
                    if (o_bits >= 8) {
                        o_bits = o_bits - 8;
                        out[out_len] = tmp >> o_bits;
                        out_len = out_len + 1;
                        tmp = tmp & ((1 << o_bits) - 1);
                    }
                    bits = 9;
                    next_shift = 512;
                    next_code = 258;
                    for (int i = 0; i < 512; i = i + 1) {
                        for (int k = 0; k < 256; k = k + 1) {
                            d_enc[i][k] = 0;
                        }
                    }
                } else {
                    bits = bits + 1;
                    next_shift = next_shift * 2;
                }
            }
        }
        tmp = (tmp << bits) | code;
        o_bits = o_bits + bits;
        if (o_bits >= 8) {
            o_bits = o_bits - 8;
            out[out_len] = tmp >> o_bits;
            out_len = out_len + 1;
            tmp = tmp & ((1 << o_bits) - 1);
        }
        tmp = (tmp << bits) | 257;
        o_bits = o_bits + bits;
        if (o_bits >= 8) {
            o_bits = o_bits - 8;
            out[out_len] = tmp >> o_bits;
            out_len = out_len + 1;
            tmp = tmp & ((1 << o_bits) - 1);
        }
        if (tmp != 0) {
            tmp = (tmp << bits) | tmp;
            o_bits = o_bits + bits;
            if (o_bits >= 8) {
                o_bits = o_bits - 8;
                out[out_len] = tmp >> o_bits;
                out_len = out_len + 1;
                tmp = tmp & ((1 << o_bits) - 1);
            }
        }
    } else {
        for (j = 0; j < 256; j = j + 1) {
            d_dec[j][2] = j;
        }
        next_code = 258;
        next_shift = 512;
        bits = 9;
        for (int i = 0; i < len; i = i + 1) {
            while (n_bits < bits) {
                if (len > 0) {
                    len = len - 1;
                    tmp = (tmp << 8) | in[i + 1];
                    n_bits = n_bits + 8;
                } else {
                    tmp = tmp << (bits - n_bits);
                    n_bits = bits;
                }
            }
            n_bits = n_bits - bits;
            code = tmp >> n_bits;
            tmp = tmp & ((1 << n_bits) - 1);
            if (code == 257) {
                break;
            }
            if (code == 256) {
                for (j = 0; j < 256; j = j + 1) {
                    d_dec[j][2] = j;
                }
                next_code = 258;
                next_shift = 512;
                bits = 9;
                continue;
            }
            if (code >= next_code) {
                out[0] = -1;
                return;
            }
            d_dec[next_code][0] = c = code;
            while (c > 255) {
                t = d_dec[c][0];
                d_dec[t][1] = c;
                c = t;
            }
            d_dec[next_code - 1][2] = c;
            while (d_dec[c][1] != 0) {
                out[out_len] = d_dec[c][2];
                out_len = out_len + 1;
                t = d_dec[c][1];
                d_dec[c][1] = 0;
                c = t;
            }
            out[out_len] = d_dec[c][2];
            out_len = out_len + 1;
            if (next_code + 1 >= next_shift) {
                if (bits + 1 > 16) {
                    out[0] = -1;
                    return;
                }
                bits = bits + 1;
                next_shift = next_shift * 2;
            }
            next_code = next_code + 1;
        }
    }
    return;
}
