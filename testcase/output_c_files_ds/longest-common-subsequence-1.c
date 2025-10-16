int lcs(char *a, int n, char *b, int m, char *s) {
    int c[100][100];
    int i;
    int j;
    int k;
    int t;
    
    for (i = 0; i <= n; i = i + 1) {
        for (j = 0; j <= m; j = j + 1) {
            c[i][j] = 0;
        }
    }
    
    for (i = 1; i <= n; i = i + 1) {
        for (j = 1; j <= m; j = j + 1) {
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
    
    t = c[n][m];
    k = t - 1;
    i = n;
    j = m;
    
    while (k >= 0) {
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
