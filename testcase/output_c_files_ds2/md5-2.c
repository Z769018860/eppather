int rol(int v, int amt) {
    int msk1 = (1 << amt) - 1;
    return ((v >> (32 - amt)) & msk1) | ((v << amt) & ~msk1);
}

int f0(int abcd[4]) {
    return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

int f1(int abcd[4]) {
    return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

int f2(int abcd[4]) {
    return abcd[1] ^ abcd[2] ^ abcd[3];
}

int f3(int abcd[4]) {
    return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

void md5(int msg[5], int mlen, int h[4]) {
    int h0[4] = {1732584193, 4023233417, 2562383102, 271733878};
    int ff[4] = {0};
    ff[0] = f0;
    ff[1] = f1;
    ff[2] = f2;
    ff[3] = f3;
    int M[4] = {1, 5, 3, 7};
    int O[4] = {0, 1, 5, 0};
    int rot0[4] = {7, 12, 17, 22};
    int rot1[4] = {5, 9, 14, 20};
    int rot2[4] = {4, 11, 16, 23};
    int rot3[4] = {6, 10, 15, 21};
    int rots[4][4] = {0};
    rots[0][0] = rot0[0];
    rots[0][1] = rot0[1];
    rots[0][2] = rot0[2];
    rots[0][3] = rot0[3];
    rots[1][0] = rot1[0];
    rots[1][1] = rot1[1];
    rots[1][2] = rot1[2];
    rots[1][3] = rot1[3];
    rots[2][0] = rot2[0];
    rots[2][1] = rot2[1];
    rots[2][2] = rot2[2];
    rots[2][3] = rot2[3];
    rots[3][0] = rot3[0];
    rots[3][1] = rot3[1];
    rots[3][2] = rot3[2];
    rots[3][3] = rot3[3];
    int kspace[64] = {0};
    int k[64] = {0};
    int abcd[4] = {0};
    int mm[16] = {0};
    int os = 0;
    int grp = 0;
    int grps = 0;
    int q = 0;
    int p = 0;
    int m = 0;
    int o = 0;
    int g = 0;
    int f = 0;
    int rotn[4] = {0};
    int i = 0;
    int s = 0;
    int pwr = 0;

    pwr = 1;
    for (i = 0; i < 32; i = i + 1) {
        pwr = pwr * 2;
    }
    for (i = 0; i < 64; i = i + 1) {
        s = 0;
        if (s < 0) {
            s = -s;
        }
        k[i] = s * pwr;
    }

    for (q = 0; q < 4; q = q + 1) {
        h[q] = h0[q];
    }

    grps = 1 + (mlen + 8) / 64;
    q = mlen + 1;
    while (q < 64 * grps) {
        q = q + 1;
    }
    q = q - 8;

    for (grp = 0; grp < grps; grp = grp + 1) {
        for (q = 0; q < 4; q = q + 1) {
            abcd[q] = h[q];
        }
        for (p = 0; p < 4; p = p + 1) {
            m = M[p];
            o = O[p];
            for (i = 0; i < 4; i = i + 1) {
                rotn[i] = rots[p][i];
            }
            for (q = 0; q < 16; q = q + 1) {
                g = (m * q + o) % 16;
                f = abcd[1] + rol(abcd[0] + ff[p](abcd) + k[q + 16 * p] + mm[g], rotn[q % 4]);
                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p = 0; p < 4; p = p + 1) {
            h[p] = h[p] + abcd[p];
        }
        os = os + 64;
    }
    return;
}
