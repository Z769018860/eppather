int poly_long_div(int nv[5], int dv[5], int r[5]) {
    int q[5];
    int i;
    int j;
    int k;
    int n;
    int d;
    int tmp;
    
    for (i = 0; i < 5; i = i + 1) {
        q[i] = 0;
        r[i] = 0;
    }
    
    n = 4;
    d = 3;
    
    for (i = 0; i < n; i = i + 1) {
        r[i] = nv[i];
    }
    
    for (k = n - d; k >= 0; k = k - 1) {
        q[k] = r[d + k - 1] / dv[d - 1];
        for (j = d + k - 1; j >= k; j = j - 1) {
            tmp = r[j] - q[k] * dv[j - k];
            r[j] = tmp;
        }
    }
    
    for (i = d; i < n; i = i + 1) {
        r[i] = 0;
    }
    
    return;
}
