void calc(int n, int p[100001][1]) {
    p[n][0] = 0;
    int k;
    for (k = 1; k <= n; k = k + 1) {
        int d = n - k * (3 * k - 1) / 2;
        if (d < 0) {
            break;
        }
        if (k & 1) {
            p[n][0] = p[n][0] + p[d][0];
        } else {
            p[n][0] = p[n][0] - p[d][0];
        }
        d = d - k;
        if (d < 0) {
            break;
        }
        if (k & 1) {
            p[n][0] = p[n][0] + p[d][0];
        } else {
            p[n][0] = p[n][0] - p[d][0];
        }
    }
    return;
}
