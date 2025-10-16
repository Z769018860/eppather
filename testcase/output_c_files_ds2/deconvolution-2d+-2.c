int deconv3(int g[3][4], int f[3][4], int h[2][3]) {
    int result[2][3];
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    
    for (i = 0; i < 2; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            result[i][j] = 0;
            for (k = 0; k < 3; k = k + 1) {
                for (l = 0; l < 4; l = l + 1) {
                    m = i + k;
                    n = j + l;
                    if (m < 3 && n < 4) {
                        result[i][j] = result[i][j] + g[m][n] * f[k][l];
                    }
                }
            }
        }
    }
    
    for (i = 0; i < 2; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            h[i][j] = result[i][j];
        }
    }
    
    return;
}
