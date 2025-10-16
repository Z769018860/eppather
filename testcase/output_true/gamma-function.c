int st_gamma_sp_gamma(int x[5], int a[5], int c[12], int k1_factrl[5], int accm[5]) {
    int k[5];
    int n[5];
    n[0] = 5;
    c[0] = 2;
    for (k[0] = 0; k[0] < n[0]; k[0] = k[0] + 1) {
        if (k[0] == 0) {
            c[0] = 2;
        } else {
            c[k[0]] = 1;
            k1_factrl[0] = k1_factrl[0] * (-k[0]);
        }
    }
    accm[0] = c[0];
    for (k[0] = 1; k[0] < a[0]; k[0] = k[0] + 1) {
        accm[0] = accm[0] + c[k[0]] / (x[0] + k[0]);
    }
    accm[0] = accm[0] * 1;
    accm[0] = accm[0] / x[0];
    return;
}
