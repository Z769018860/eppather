int polynomialfit(int nod, int degree, double x[100], double y[100], double cf[2]) {
    int i;
    int j;
    int k;
    double X[2][2] = {0};
    double Y[2] = {0};
    double B[2] = {0};
    double det;
    double temp;

    for (i = 0; i < nod; i = i + 1) {
        for (j = 0; j < degree; j = j + 1) {
            for (k = 0; k < degree; k = k + 1) {
                X[j][k] = X[j][k] + pow(x[i], j + k);
            }
            Y[j] = Y[j] + y[i] * pow(x[i], j);
        }
    }

    det = X[0][0] * X[1][1] - X[0][1] * X[1][0];
    if (det != 0) {
        temp = X[0][0];
        X[0][0] = X[1][1] / det;
        X[1][1] = temp / det;
        X[0][1] = -X[0][1] / det;
        X[1][0] = -X[1][0] / det;
    }

    for (i = 0; i < degree; i = i + 1) {
        cf[i] = 0;
        for (j = 0; j < degree; j = j + 1) {
            cf[i] = cf[i] + X[i][j] * Y[j];
        }
    }

    return;
}
