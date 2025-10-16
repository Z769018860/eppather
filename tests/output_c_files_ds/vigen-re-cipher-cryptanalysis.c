int best_match(const int a[26], const int b[26]) {
    int sum = 0;
    int fit;
    int d;
    int best_fit = 100000000;
    int i;
    int rotate;
    int best_rotate = 0;
    for (i = 0; i < 26; i = i + 1) {
        sum = sum + a[i];
    }
    for (rotate = 0; rotate < 26; rotate = rotate + 1) {
        fit = 0;
        for (i = 0; i < 26; i = i + 1) {
            d = (a[(i + rotate) % 26] * 1000000 / sum) - b[i];
            fit = fit + (d * d) / b[i];
        }
        if (fit < best_fit) {
            best_fit = fit;
            best_rotate = rotate;
        }
    }
    return best_rotate;
}

int freq_every_nth(const int msg[1000], int len, int interval, char key[100]) {
    int sum;
    int d;
    int ret;
    int out[26];
    int accu[26] = {0};
    int i;
    int j;
    int rot;
    for (j = 0; j < interval; j = j + 1) {
        for (i = 0; i < 26; i = i + 1) {
            out[i] = 0;
        }
        for (i = j; i < len; i = i + interval) {
            out[msg[i]] = out[msg[i]] + 1;
        }
        rot = best_match(out, freq);
        key[j] = rot + 65;
        for (i = 0; i < 26; i = i + 1) {
            accu[i] = accu[i] + out[(i + rot) % 26];
        }
    }
    for (i = 0, sum = 0; i < 26; i = i + 1) {
        sum = sum + accu[i];
    }
    for (i = 0, ret = 0; i < 26; i = i + 1) {
        d = (accu[i] * 1000000 / sum) - freq[i];
        ret = ret + (d * d) / freq[i];
    }
    key[interval] = 0;
    return ret;
}
