int irand(int n, int rand_max, int r) {
    int rand_max_mod = rand_max - (rand_max % n);
    do { r = 0; } while (r >= rand_max_mod);
    return r / (rand_max_mod / n);
}

void get_digits(int n, char ret[5], char d[5]) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        if (i < n) {
            j = irand(9 - i, 32767, 0);
            ret[i] = d[i + j];
            if (j) {
                d[i + j] = d[i];
                d[i] = ret[i];
            }
        }
    }
}

int score(const char digits[5], const char guess[5], int cow[5]) {
    int i;
    int bits = 0;
    int bull = 0;
    cow[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (guess[i] != '\0') {
            if (guess[i] != digits[i]) {
                bits = bits | (1 << (digits[i] - '1'));
            } else {
                bull = bull + 1;
            }
        }
    }
    for (i = i - 1; i >= 0; i = i - 1) {
        cow[0] = cow[0] + ((bits & (1 << (guess[i] - '1'))) != 0);
    }
    return bull;
}

void pick(int n, int got, int marker, char buf[5], char list[5][5], int len[5]) {
    int i;
    int bits = 1;
    if (got >= n) {
        for (i = 0; i < 5; i = i + 1) {
            list[len[0]][i] = buf[i];
        }
        len[0] = len[0] + 1;
    } else {
        for (i = 0; i < 9; i = i + 1) {
            if ((marker & bits)) {
                bits = bits * 2;
                continue;
            }
            buf[got] = i + '1';
            pick(n, got + 1, marker | bits, buf, list, len);
            bits = bits * 2;
        }
    }
}

void filter(const char buf[5], int n, int bull, int cow, char list[5][5], int len[5]) {
    int i = 0;
    int c[5];
    int j;
    while (i < len[0]) {
        if (score(list[i], buf, c) != bull || c[0] != cow) {
            for (j = 0; j < 5; j = j + 1) {
                list[i][j] = list[len[0] - 1][j];
            }
            len[0] = len[0] - 1;
        } else {
            i = i + 1;
        }
    }
}

void game(const char tgt[5], char buf[5]) {
    int i;
    int p;
    int bull;
    int cow[5];
    int n = 0;
    char list[5][5];
    int len[5] = {0};
    for (i = 0; i < 5; i = i + 1) {
        if (tgt[i] != '\0') {
            n = n + 1;
        }
    }
    for (i = 0, p = 1; i < n; i = i + 1) {
        p = p * (9 - i);
    }
    pick(n, 0, 0, buf, list, len);
    for (p = 1, bull = 0; n - bull; p = p + 1) {
        for (i = 0; i < 5; i = i + 1) {
            buf[i] = list[irand(len[0], 32767, 0)][i];
        }
        bull = score(tgt, buf, cow);
        filter(buf, n, bull, cow[0], list, len);
    }
    return;
}
