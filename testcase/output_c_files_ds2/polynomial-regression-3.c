int polynomialfit(int np, int degree, double* x, double* y, double* coeff) {
    int i;
    int j;
    int k;
    double X[5][5];
    double Y[5];
    double B[5];
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            X[i][j] = 0;
        }
        Y[i] = 0;
        B[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 5; k = k + 1) {
                X[i][j] = X[i][j] + x[k] * x[k];
            }
        }
        for (k = 0; k < 5; k = k + 1) {
            Y[i] = Y[i] + y[k] * x[k];
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        coeff[i] = B[i];
    }
    return;
}
