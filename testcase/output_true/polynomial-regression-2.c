void polynomialfit(int obs, int degree, int dx[5], int dy[5], int store[5]) {
    int X[5][5];
    int y[5];
    int c[5];
    int cov[5][5];
    int chisq;
    int i;
    int j;

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            int pow_val;
            pow_val = 1;
            for (int k = 0; k < j; k = k + 1) {
                pow_val = pow_val * dx[i];
            }
            X[i][j] = pow_val;
        }
        y[i] = dy[i];
    }

    for (i = 0; i < 5; i = i + 1) {
        store[i] = c[i];
    }

    return;
}
