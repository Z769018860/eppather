void linear_fit(int n) {
    double w[15] = {52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46};
    double h[15] = {1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83};
    double X[15][3];
    double Y[15];
    double beta[3];
    double cov[3][3];
    double chisq;
    
    for (int i = 0; i < n; i = i + 1) {
        Y[i] = w[i];
        X[i][0] = 1;
        X[i][1] = h[i];
        X[i][2] = h[i] * h[i];
    }
    
    for (int i = 0; i < 3; i = i + 1) {
        beta[i] = 0;
        for (int j = 0; j < 3; j = j + 1) {
            cov[i][j] = 0;
        }
    }
    
    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            beta[j] = beta[j] + X[i][j] * Y[i];
        }
    }
    
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            for (int k = 0; k < n; k = k + 1) {
                cov[i][j] = cov[i][j] + X[k][i] * X[k][j];
            }
        }
    }
    
    chisq = 0;
    for (int i = 0; i < n; i = i + 1) {
        double sum = 0;
        for (int j = 0; j < 3; j = j + 1) {
            sum = sum + beta[j] * X[i][j];
        }
        chisq = chisq + (Y[i] - sum) * (Y[i] - sum);
    }
    
    return;
}
