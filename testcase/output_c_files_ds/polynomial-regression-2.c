int polynomialfit(int obs, int degree, int* dx, int* dy, int* store) {
    int X[100][100];
    int y[100];
    int c[100];
    int cov[100][100];
    int chisq;
    int i;
    int j;
    int k;
    int temp;

    for (i = 0; i < obs; i = i + 1) {
        for (j = 0; j < degree; j = j + 1) {
            temp = 1;
            for (k = 0; k < j; k = k + 1) {
                temp = temp * dx[i];
            }
            X[i][j] = temp;
        }
        y[i] = dy[i];
    }

    for (i = 0; i < degree; i = i + 1) {
        c[i] = 0;
        for (j = 0; j < degree; j = j + 1) {
            cov[i][j] = 0;
        }
    }

    for (i = 0; i < degree; i = i + 1) {
        store[i] = c[i];
    }

    return 1;
}
