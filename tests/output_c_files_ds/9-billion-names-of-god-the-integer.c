int p[100001];

void calc(int n) {
    p[n] = 0;
    for (int k = 1; k <= n; k = k + 1) {
        int d = n - k * (3 * k - 1) / 2;
        if (d < 0) {
            break;
        }
        if (k & 1) {
            p[n] = p[n] + p[d];
        } else {
            p[n] = p[n] - p[d];
        }
        d = d - k;
        if (d < 0) {
            break;
        }
        if (k & 1) {
            p[n] = p[n] + p[d];
        } else {
            p[n] = p[n] - p[d];
        }
    }
    return;
}
