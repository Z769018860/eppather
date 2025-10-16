int best_match(int a[26], int b[26]) {
    int sum = 0;
    int fit;
    int d;
    int best_fit = 1000000000;
    int i;
    int rotate;
    int best_rotate = 0;
    for (i = 0; i < 26; i = i + 1) {
        sum = sum + a[i];
    }
    for (rotate = 0; rotate < 26; rotate = rotate + 1) {
        fit = 0;
        for (i = 0; i < 26; i = i + 1) {
            d = a[(i + rotate) % 26] / sum - b[i];
            fit = fit + d * d / b[i];
        }
        if (fit < best_fit) {
            best_fit = fit;
            best_rotate = rotate;
        }
    }
    return best_rotate;
}

int freq_every_nth(int msg[5], int len, int interval, int key[5]) {
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
        key[j] = best_match(out, freq);
        key[j] = key[j] + 65;
        for (i = 0; i < 26; i = i + 1) {
            accu[i] = accu[i] + out[(i + rot) % 26];
        }
    }
    for (i = 0, sum = 0; i < 26; i = i + 1) {
        sum = sum + accu[i];
    }
    for (i = 0, ret = 0; i < 26; i = i + 1) {
        d = accu[i] / sum - freq[i];
        ret = ret + d * d / freq[i];
    }
    key[interval] = 0;
    return ret;
}

int freq[26] = {
    8167, 1492, 2782, 4253, 12702, 2228, 2015,
    6094, 6966, 153, 772, 4025, 2406, 6749,
    7507, 1929, 95, 5987, 6327, 9056, 2758,
    978, 2360, 150, 1974, 74
};

return;
