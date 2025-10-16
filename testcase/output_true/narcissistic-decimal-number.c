void narc(int n, int power[10][5], int dsum[82][5], int cnt[10]) {
    int len;
    len = n;
    int i;
    for (i = 0; i < 10; i = i + 1) {
        int j;
        for (j = 0; j < 5; j = j + 1) {
            power[i][j] = 0;
        }
        int k;
        for (k = 0; k < n; k = k + 1) {
            power[i][0] = power[i][0] * i;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        dsum[n][i] = 0;
    }
    int pos;
    pos = n;
    int d;
    d = 9;
    if (pos == 0) {
        int s[82];
        int out[10];
        for (i = 0; i < 10; i = i + 1) {
            out[i] = 0;
        }
        int temp;
        temp = dsum[0][0];
        int idx;
        idx = 0;
        while (temp != 0) {
            s[idx] = temp % 10;
            temp = temp / 10;
            idx = idx + 1;
        }
        int valid;
        valid = 1;
        for (i = 0; i < idx; i = i + 1) {
            int c;
            c = s[i];
            out[c] = out[c] + 1;
            if (out[c] > cnt[c]) {
                valid = 0;
                break;
            }
        }
        if (valid == 1 && idx == len) {
            return;
        }
    } else {
        do {
            dsum[pos-1][0] = dsum[pos][0] + power[d][0];
            cnt[d] = cnt[d] + 1;
            narc(pos - 1, power, dsum, cnt);
            cnt[d] = cnt[d] - 1;
            d = d - 1;
        } while (d >= 0);
    }
    return;
}
