void deconv(int g[], int lg, int f[], int lf, int out[]) {
    int PI = 3;
    int ns = 1;
    int n = 1;
    while (n < lg) {
        n = n * 2;
    }
    int g2[5][2];
    int f2[5][2];
    for (int i = 0; i < lg; i = i + 1) {
        g2[i][0] = g[i];
        g2[i][1] = 0;
    }
    for (int i = lg; i < n; i = i + 1) {
        g2[i][0] = 0;
        g2[i][1] = 0;
    }
    for (int i = 0; i < lf; i = i + 1) {
        f2[i][0] = f[i];
        f2[i][1] = 0;
    }
    for (int i = lf; i < n; i = i + 1) {
        f2[i][0] = 0;
        f2[i][1] = 0;
    }
    int h[5][2];
    for (int i = 0; i < n; i = i + 1) {
        int denom = f2[i][0] * f2[i][0] + f2[i][1] * f2[i][1];
        h[i][0] = (g2[i][0] * f2[i][0] + g2[i][1] * f2[i][1]) / denom;
        h[i][1] = (g2[i][1] * f2[i][0] - g2[i][0] * f2[i][1]) / denom;
    }
    for (int i = lf - lg; i <= 0; i = i + 1) {
        int idx = (i + n) % n;
        out[-i] = h[idx][0] / 32;
    }
    return;
}
