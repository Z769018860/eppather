void cubic_bezier(int img[5], int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int r, int g, int b) {
    int t[5];
    int x[5];
    int y[5];
    int i;
    int j;
    int n;
    n = 5;
    for (i = 0; i < n; i = i + 1) {
        t[0] = i;
        t[0] = t[0] / (n - 1);
        x[0] = 1 - t[0];
        x[0] = x[0] * x[0] * x[0] * x1 + 3 * x[0] * x[0] * t[0] * x2 + 3 * x[0] * t[0] * t[0] * x3 + t[0] * t[0] * t[0] * x4;
        y[0] = 1 - t[0];
        y[0] = y[0] * y[0] * y[0] * y1 + 3 * y[0] * y[0] * t[0] * y2 + 3 * y[0] * t[0] * t[0] * y3 + t[0] * t[0] * t[0] * y4;
        for (j = 0; j < n; j = j + 1) {
            img[0] = x[0];
            img[1] = y[0];
            img[2] = r;
            img[3] = g;
            img[4] = b;
        }
    }
    return;
}
