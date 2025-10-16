void cholesky(int A[5][5], int L[5][5], int n) {
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            L[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < (i + 1); j = j + 1) {
            int s = 0;
            for (int k = 0; k < j; k = k + 1) {
                s = s + L[i][k] * L[j][k];
            }
            if (i == j) {
                L[i][j] = 0;
            } else {
                L[i][j] = (1 / L[j][j] * (A[i][j] - s));
            }
        }
    }
    return;
}
