int fac_fib(int mode, int n) {
    int result[10];
    int i;
    int j;
    for (i = 0; i < 10; i = i + 1) {
        result[i] = 0;
    }
    if (mode == 0) {
        for (i = 1; i < n; i = i + 1) {
            if (i == 1) {
                result[i] = 1;
            } else {
                result[i] = i * result[i - 1];
            }
        }
    } else {
        for (i = 1; i < n; i = i + 1) {
            if (i == 1 || i == 2) {
                result[i] = 1;
            } else {
                result[i] = result[i - 1] + result[i - 2];
            }
        }
    }
    return result[n - 1];
}
