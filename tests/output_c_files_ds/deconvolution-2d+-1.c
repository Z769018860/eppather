void deconv3(int g[4][4][6], int f[3][2][3], int out[2][3][4]) {
    int gx = 4;
    int gy = 4;
    int gz = 6;
    int fx = 3;
    int fy = 2;
    int fz = 3;
    int hx = gx - fx + 1;
    int hy = gy - fy + 1;
    int hz = gz - fz + 1;
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int sum;

    for (i = 0; i < hx; i = i + 1) {
        for (j = 0; j < hy; j = j + 1) {
            for (k = 0; k < hz; k = k + 1) {
                sum = 0;
                for (l = 0; l < fx; l = l + 1) {
                    for (m = 0; m < fy; m = m + 1) {
                        for (n = 0; n < fz; n = n + 1) {
                            sum = sum + g[i + l][j + m][k + n] * f[l][m][n];
                        }
                    }
                }
                out[i][j][k] = sum / 4;
            }
        }
    }
    return;
}
