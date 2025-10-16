void polynomialfit(int np, int degree, double* x, double* y, double* coeff) {
    int i;
    int j;
    int k;
    double X[2*degree+1];
    for (i = 0; i < 2*degree+1; i = i + 1) {
        X[i] = 0;
        for (j = 0; j < np; j = j + 1) {
            X[i] = X[i] + pow(x[j], i);
        }
    }
    double B[degree+1][degree+2];
    for (i = 0; i <= degree; i = i + 1) {
        for (j = 0; j <= degree; j = j + 1) {
            B[i][j] = X[i+j];
        }
    }
    double Y[degree+1];
    for (i = 0; i < degree+1; i = i + 1) {
        Y[i] = 0;
        for (j = 0; j < np; j = j + 1) {
            Y[i] = Y[i] + pow(x[j], i) * y[j];
        }
    }
    for (i = 0; i <= degree; i = i + 1) {
        B[i][degree+1] = Y[i];
    }
    for (k = 0; k <= degree; k = k + 1) {
        for (i = 0; i <= degree; i = i + 1) {
            if (i != k) {
                double t = B[i][k] / B[k][k];
                for (j = 0; j <= degree+1; j = j + 1) {
                    B[i][j] = B[i][j] - t * B[k][j];
                }
            }
        }
    }
    for (i = 0; i <= degree; i = i + 1) {
        coeff[i] = B[i][degree+1] / B[i][i];
    }
    return;
}
