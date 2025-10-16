double linear_regression() {
    double w[15] = {52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46};
    double h[15] = {1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83};
    double X[15][3];
    double Y[15];
    double beta[3] = {0};
    double cov[3][3] = {0};
    double chisq = 0;
    int n = 15;
    
    for (int i = 0; i < n; i = i + 1) {
        Y[i] = w[i];
        X[i][0] = 1;
        X[i][1] = h[i];
        X[i][2] = h[i] * h[i];
    }
    
    double XtX[3][3] = {0};
    double XtY[3] = {0};
    
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            for (int k = 0; k < n; k = k + 1) {
                XtX[i][j] = XtX[i][j] + X[k][i] * X[k][j];
            }
        }
    }
    
    for (int i = 0; i < 3; i = i + 1) {
        for (int k = 0; k < n; k = k + 1) {
            XtY[i] = XtY[i] + X[k][i] * Y[k];
        }
    }
    
    double det = XtX[0][0] * (XtX[1][1] * XtX[2][2] - XtX[1][2] * XtX[2][1]) - 
                 XtX[0][1] * (XtX[1][0] * XtX[2][2] - XtX[1][2] * XtX[2][0]) + 
                 XtX[0][2] * (XtX[1][0] * XtX[2][1] - XtX[1][1] * XtX[2][0]);
    
    if (det != 0) {
        double invXtX[3][3];
        invXtX[0][0] = (XtX[1][1] * XtX[2][2] - XtX[1][2] * XtX[2][1]) / det;
        invXtX[0][1] = (XtX[0][2] * XtX[2][1] - XtX[0][1] * XtX[2][2]) / det;
        invXtX[0][2] = (XtX[0][1] * XtX[1][2] - XtX[0][2] * XtX[1][1]) / det;
        invXtX[1][0] = (XtX[1][2] * XtX[2][0] - XtX[1][0] * XtX[2][2]) / det;
        invXtX[1][1] = (XtX[0][0] * XtX[2][2] - XtX[0][2] * XtX[2][0]) / det;
        invXtX[1][2] = (XtX[0][2] * XtX[1][0] - XtX[0][0] * XtX[1][2]) / det;
        invXtX[2][0] = (XtX[1][0] * XtX[2][1] - XtX[1][1] * XtX[2][0]) / det;
        invXtX[2][1] = (XtX[0][1] * XtX[2][0] - XtX[0][0] * XtX[2][1]) / det;
        invXtX[2][2] = (XtX[0][0] * XtX[1][1] - XtX[0][1] * XtX[1][0]) / det;
        
        for (int i = 0; i < 3; i = i + 1) {
            beta[i] = 0;
            for (int j = 0; j < 3; j = j + 1) {
                beta[i] = beta[i] + invXtX[i][j] * XtY[j];
            }
        }
    }
    
    return beta[0];
}
