void polynomialfit(int nod, int degree, double* x, double* y, double* cf) {
    int i;
    int j;
    int k;
    double X[5][5];
    double Y[5];
    double B[5];
    double sum;
    
    for (i = 0; i < 5; i = i + 1) {
        Y[i] = 0.0;
        B[i] = 0.0;
        for (j = 0; j < 5; j = j + 1) {
            X[i][j] = 0.0;
        }
    }
    
    for (i = 0; i < nod; i = i + 1) {
        for (j = 0; j < degree + 1; j = j + 1) {
            for (k = 0; k < degree + 1; k = k + 1) {
                X[j][k] = X[j][k] + pow(x[i], j + k);
            }
            Y[j] = Y[j] + y[i] * pow(x[i], j);
        }
    }
    
    for (i = 0; i < degree + 1; i = i + 1) {
        for (j = 0; j < degree + 1; j = j + 1) {
            sum = 0.0;
            for (k = 0; k < degree + 1; k = k + 1) {
                sum = sum + X[i][k] * B[k];
            }
            B[i] = Y[i] - sum;
        }
    }
    
    for (i = 0; i < degree + 1; i = i + 1) {
        cf[i] = B[i];
    }
    
    return;
}
