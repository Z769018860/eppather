int rand5_7(int rand_max, int r1, int r2) {
    int r;
    for (r = 0; r < 1; r = r + 1) {
        r = r1 * 5 + r2;
        if (r >= 27) {
            r = 0;
        } else {
            r = r / 3 - 1;
        }
    }
    return r;
}

int check(int n, int cnt, int delta, int bins[5], int gen_val[5]) {
    int i;
    int ratio_num;
    int ratio_den;
    int result;
    for (i = 0; i < 5; i = i + 1) {
        bins[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        gen_val[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        bins[gen_val[0] - 1] = bins[gen_val[0] - 1] + 1;
    }
    result = 1;
    for (i = 0; i < n; i = i + 1) {
        ratio_num = bins[i] * n;
        ratio_den = cnt;
        if (ratio_num / ratio_den - 1 > -delta && ratio_num / ratio_den - 1 < delta) {
            continue;
        }
        result = 0;
        break;
    }
    return result;
}

void merged_function(int rand_max, int r1, int r2, int n, int cnt, int delta, int bins[5], int gen_val[5]) {
    int r;
    r = rand5_7(rand_max, r1, r2);
    gen_val[0] = r;
    check(n, cnt, delta, bins, gen_val);
    return;
}
