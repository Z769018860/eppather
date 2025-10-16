void coef_is_prime_show(int n, int* result) {
    int c[100];
    int i;
    int j;
    int k;
    int temp;
    
    if (n < 0 || n > 63) {
        return;
    }
    
    c[0] = 1;
    for (i = 0; i < n; i = i + 1) {
        c[0] = -c[0];
        for (j = i; j > 0; j = j - 1) {
            c[j] = c[j - 1] - c[j];
        }
        c[1 + i] = 1;
    }
    
    c[0] = c[0] + 1;
    c[n] = c[n] - 1;
    i = n;
    temp = 0;
    for (k = 0; k < n + 1; k = k + 1) {
        if (i >= 0 && (c[i] % n) == 0) {
            temp = 1;
        }
        i = i - 1;
    }
    
    if (temp == 0) {
        result[0] = 1;
    } else {
        result[0] = 0;
    }
    
    return;
}
