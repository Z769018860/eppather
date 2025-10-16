double det_in(double in[5][5], int n, int perm) {
    if (n == 1) {
        return in[0][0];
    }
    double sum = 0;
    double m[4][4];
    int new_n = n - 1;
    for (int i = 0; i < new_n; i = i + 1) {
        for (int j = 0; j < new_n; j = j + 1) {
            m[i][j] = in[i + 1][j + 1];
        }
    }
    int sgn = 1;
    for (int i = 0; i <= new_n; i = i + 1) {
        sum = sum + sgn * (in[i][0] * det_in(m, new_n, perm));
        if (i == new_n) {
            break;
        }
        for (int j = 0; j < new_n; j = j + 1) {
            m[i][j] = in[i][j + 1];
        }
        if (perm == 0) {
            sgn = -sgn;
        }
    }
    return sum;
}

double det(double in[25], int n, int perm) {
    double m[5][5];
    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            m[i][j] = in[i * n + j];
        }
    }
    return det_in(m, n, perm);
}

return;
