int lzw_encode_decode(int in[1024], int in_len, int max_bits, int out[1024]) {
    int d_next[512][256];
    int out_len = 0;
    int bits = 9;
    int next_shift = 512;
    int next_code = 258;
    int code;
    int c;
    int nc;
    int tmp = 0;
    int o_bits = 0;
    int i;
    int j;
    int t;

    for (i = 0; i < 512; i = i + 1) {
        for (j = 0; j < 256; j = j + 1) {
            d_next[i][j] = 0;
        }
    }

    if (max_bits > 15) {
        max_bits = 15;
    }
    if (max_bits < 9) {
        max_bits = 12;
    }

    code = in[0];
    for (i = 1; i < in_len; i = i + 1) {
        c = in[i];
        nc = d_next[code][c];
        if (nc) {
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
            d_next[code][c] = next_code;
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
                for (j = 0; j < 512; j = j + 1) {
                    for (t = 0; t < 256; t = t + 1) {
                        d_next[j][t] = 0;
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

    if (tmp) {
        tmp = (tmp << bits) | tmp;
        o_bits = o_bits + bits;
        if (o_bits >= 8) {
            o_bits = o_bits - 8;
            out[out_len] = tmp >> o_bits;
            out_len = out_len + 1;
            tmp = tmp & ((1 << o_bits) - 1);
        }
    }

    return out_len;
}
