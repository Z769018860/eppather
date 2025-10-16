int is_hex(int s[64]) {
    int i;
    for (i = 0; i < 64; i = i + 1) {
        if (!((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 70) || (s[i] >= 97 && s[i] <= 102))) {
            return 0;
        }
    }
    return 1;
}

void str_to_byte(int src[64], int dst[32], int n) {
    int i;
    for (i = 0; i < n; i = i + 1) {
        int idx = n - i - 1;
        int val = 0;
        int j;
        for (j = 0; j < 2; j = j + 1) {
            int c = src[idx * 2 + j];
            if (c >= 48 && c <= 57) {
                val = val * 16 + (c - 48);
            } else if (c >= 65 && c <= 70) {
                val = val * 16 + (c - 55);
            } else if (c >= 97 && c <= 102) {
                val = val * 16 + (c - 87);
            }
        }
        dst[idx] = val;
    }
}

void base58(int s[25], int out[34]) {
    int tmpl[58] = {49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,74,75,76,77,78,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102,103,104,105,106,107,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    int buf[34];
    int c;
    int i;
    int n;
    int j;

    for (n = 0; n < 34; n = n + 1) {
        out[n] = 0;
    }

    n = 34;
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
    while (n < 34 && out[n] == 49) {
        n = n + 1;
    }

    for (i = 0; i < 34 - n; i = i + 1) {
        out[i] = out[i + n];
    }
    for (i = 34 - n; i < 34; i = i + 1) {
        out[i] = 0;
    }
}

void coin_encode(int x[64], int y[64], int out[34]) {
    int s[65];
    int rmd[25];
    int sha256_temp1[32];
    int sha256_temp2[32];
    int i;
    int j;
    int k;
    int coin_ver = 0;

    if (!is_hex(x) || !is_hex(y)) {
        return;
    }

    s[0] = 4;
    str_to_byte(x, s + 1, 32);
    str_to_byte(y, s + 33, 32);

    rmd[0] = coin_ver;

    for (i = 0; i < 32; i = i + 1) {
        sha256_temp1[i] = 0;
    }
    for (i = 0; i < 65; i = i + 1) {
        for (j = 0; j < 8; j = j + 1) {
            if ((s[i] >> (7 - j)) & 1) {
                sha256_temp1[j] = sha256_temp1[j] ^ 1;
            }
        }
    }

    for (i = 1; i < 21; i = i + 1) {
        rmd[i] = sha256_temp1[i - 1];
    }

    for (i = 0; i < 32; i = i + 1) {
        sha256_temp2[i] = 0;
    }
    for (i = 0; i < 21; i = i + 1) {
        for (j = 0; j < 8; j = j + 1) {
            if ((rmd[i] >> (7 - j)) & 1) {
                sha256_temp2[j] = sha256_temp2[j] ^ 1;
            }
        }
    }

    for (i = 21; i < 25; i = i + 1) {
        rmd[i] = sha256_temp2[i - 21];
    }

    base58(rmd, out);
    return;
}
