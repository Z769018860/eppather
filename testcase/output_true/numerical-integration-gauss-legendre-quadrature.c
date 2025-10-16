void lege_coef_roots_inte(int n, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20) {
    double Pi[5];
    double lroots[5];
    double weight[5];
    double lcoef[6][6];
    int i;
    int j;
    int k;
    int m;
    double x[5];
    double x1[5];
    double s[5];
    double c1[5];
    double c2[5];
    double sum[5];

    for (i = 0; i < 6; i = i + 1) {
        for (j = 0; j < 6; j = j + 1) {
            lcoef[i][j] = 0.0;
        }
    }

    lcoef[0][0] = 1.0;
    lcoef[1][1] = 1.0;

    for (n = 2; n <= 5; n = n + 1) {
        lcoef[n][0] = -(n - 1) * lcoef[n - 2][0] / n;
        for (i = 1; i <= n; i = i + 1) {
            lcoef[n][i] = ((2 * n - 1) * lcoef[n - 1][i - 1] - (n - 1) * lcoef[n - 2][i]) / n;
        }
    }

    Pi[0] = 3.14159265358979323846;

    for (i = 1; i <= 5; i = i + 1) {
        x[0] = cos(Pi[0] * (i - 0.25) / (5 + 0.5));
        do {
            x1[0] = x[0];
            s[0] = lcoef[5][5];
            for (j = 5; j > 0; j = j - 1) {
                s[0] = s[0] * x[0] + lcoef[5][j - 1];
            }
            x[0] = x[0] - s[0] / (5 * (x[0] * s[0] - lcoef[4][4]) / (x[0] * x[0] - 1));
        } while ((x[0] > x1[0] ? x[0] - x1[0] : x1[0] - x[0]) > 2e-16);

        lroots[i - 1] = x[0];
        s[0] = lcoef[5][5];
        for (j = 5; j > 0; j = j - 1) {
            s[0] = s[0] * x[0] + lcoef[5][j - 1];
        }
        x1[0] = 5 * (x[0] * s[0] - lcoef[4][4]) / (x[0] * x[0] - 1);
        weight[i - 1] = 2 / ((1 - x[0] * x[0]) * x1[0] * x1[0]);
    }

    c1[0] = (n1 - n2) / 2;
    c2[0] = (n1 + n2) / 2;
    sum[0] = 0.0;

    for (i = 0; i < 5; i = i + 1) {
        sum[0] = sum[0] + weight[i] * (c1[0] * lroots[i] + c2[0]);
    }

    return;
}
