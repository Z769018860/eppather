int lcs(int a[5], int n, int b[5], int m, int s[5]) {
    int c[6][6];
    int z[36];
    int i;
    int j;
    int k;
    int t;
    for (i = 0; i <= 5; i = i + 1) {
        for (j = 0; j <= 5; j = j + 1) {
            z[i * 6 + j] = 0;
        }
    }
    for (i = 0; i <= 5; i = i + 1) {
        for (j = 0; j <= 5; j = j + 1) {
            c[i][j] = z[i * 6 + j];
        }
    }
    for (i = 1; i <= 5; i = i + 1) {
        for (j = 1; j <= 5; j = j + 1) {
            if (a[i - 1] == b[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else {
                if (c[i - 1][j] > c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                } else {
                    c[i][j] = c[i][j - 1];
                }
            }
        }
    }
    t = c[5][5];
    for (i = 5, j = 5, k = t - 1; k >= 0;) {
        if (a[i - 1] == b[j - 1]) {
            s[k] = a[i - 1];
            i = i - 1;
            j = j - 1;
            k = k - 1;
        } else {
            if (c[i][j - 1] > c[i - 1][j]) {
                j = j - 1;
            } else {
                i = i - 1;
            }
        }
    }
    return t;
}
