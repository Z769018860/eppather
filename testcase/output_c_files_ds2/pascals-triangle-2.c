int pascals(int *x, int *y, int d) {
    int n1;
    n1 = 32;
    int i;
    for (i = 1; i < d; i = i + 1) {
        y[i] = x[i - 1] + x[i];
    }
    if (n1 > d) {
        pascals(y, x, d + 1);
    }
    return;
}
