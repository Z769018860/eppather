int power[10][100];
int dsum[82][100];
int cnt[10];
int len;

void check_perm(void) {
    int s[82];
    int i;
    int c;
    int out[10];
    int temp;
    int j;
    int k;
    
    for (i = 0; i < 10; i = i + 1) {
        out[i] = 0;
    }
    
    temp = dsum[0][0];
    i = 0;
    while (temp != 0) {
        s[i] = temp % 10;
        temp = temp / 10;
        i = i + 1;
    }
    
    for (j = 0; j < i; j = j + 1) {
        c = s[j];
        out[c] = out[c] + 1;
        if (out[c] > cnt[c]) {
            return;
        }
    }
    
    if (i == len) {
        return;
    }
}

void narc_(int pos, int d) {
    if (pos == 0) {
        check_perm();
        return;
    }
    
    for (;;) {
        for (int k = 0; k < 100; k = k + 1) {
            dsum[pos - 1][k] = dsum[pos][k] + power[d][k];
        }
        cnt[d] = cnt[d] + 1;
        narc_(pos - 1, d);
        cnt[d] = cnt[d] - 1;
        d = d - 1;
        if (d < 0) {
            break;
        }
    }
}

void narc(int n) {
    int i;
    int j;
    int temp;
    
    len = n;
    for (i = 0; i < 10; i = i + 1) {
        temp = 1;
        for (j = 0; j < n; j = j + 1) {
            temp = temp * i;
        }
        power[i][0] = temp;
    }
    
    for (i = 0; i < 100; i = i + 1) {
        dsum[n][i] = 0;
    }
    
    narc_(n, 9);
    return;
}
