int irand(int n, int rand_val) {
    int r;
    int rand_max;
    rand_max = 32767 - (32767 % n);
    do {
        r = rand_val;
        rand_val = (rand_val * 1103515245 + 12345) & 32767;
    } while (r >= rand_max);
    return r / (rand_max / n);
}

void get_digits(int n, char ret[10]) {
    int i;
    int j;
    char d[10] = "123456789";
    int rand_val = 12345;

    for (i = 0; i < n; i = i + 1) {
        j = irand(9 - i, rand_val);
        rand_val = (rand_val * 1103515245 + 12345) & 32767;
        ret[i] = d[i + j];
        if (j) {
            d[i + j] = d[i];
            d[i] = ret[i];
        }
    }
}

int score(const char digits[10], const char guess[10], int cow[1]) {
    int i;
    int bits;
    int bull;
    bits = 0;
    bull = 0;
    cow[0] = 0;

    for (i = 0; guess[i] != '\0'; i = i + 1) {
        if (guess[i] != digits[i]) {
            bits = bits | (1 << (digits[i] - '1'));
        } else {
            bull = bull + 1;
        }
    }

    while (i > 0) {
        i = i - 1;
        cow[0] = cow[0] + ((bits & (1 << (guess[i] - '1'))) != 0);
    }

    return bull;
}

void pick(int n, int got, int marker, char buf[10], char list[1000][10], int len[1]) {
    int i;
    int bits;
    bits = 1;

    if (got >= n) {
        for (i = 0; i < n + 1; i = i + 1) {
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

void filter(const char buf[10], int n, int bull, int cow, char list[1000][10], int len[1]) {
    int i;
    int c[1];
    i = 0;

    while (i < len[0]) {
        if (score(list[i], buf, c) != bull || c[0] != cow) {
            for (int j = 0; j < n + 1; j = j + 1) {
                list[i][j] = list[len[0] - 1][j];
            }
            len[0] = len[0] - 1;
        } else {
            i = i + 1;
        }
    }
}

void game(const char tgt[10], char buf[10], char list[1000][10]) {
    int i;
    int p;
    int bull;
    int cow[1];
    int n;
    int len[1];
    len[0] = 0;
    n = 0;

    while (tgt[n] != '\0') {
        n = n + 1;
    }

    for (i = 0, p = 1; i < n; i = i + 1) {
        p = p * (9 - i);
    }

    pick(n, 0, 0, buf, list, len);
    for (p = 1, bull = 0; n - bull; p = p + 1) {
        int rand_val = 12345;
        int idx = irand(len[0], rand_val);
        for (i = 0; i < n + 1; i = i + 1) {
            buf[i] = list[idx][i];
        }
        bull = score(tgt, buf, cow);
        filter(buf, n, bull, cow[0], list, len);
    }
    return;
}
