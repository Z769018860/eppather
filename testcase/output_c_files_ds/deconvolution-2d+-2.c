int deconv3(int g[3][4], int f[3][4], int h[2][3]) {
    int result[2][3];
    int i;
    int j;
    int k;
    int l;
    int sum;
    for (i = 0; i < 2; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            sum = 0;
            for (k = 0; k < 3; k = k + 1) {
                for (l = 0; l < 4; l = l + 1) {
                    if (i + k < 3 && j + l < 4) {
                        sum = sum + g[i + k][j + l] * f[k][l];
                    }
                }
            }
            h[i][j] = sum;
        }
    }
    return;
}
