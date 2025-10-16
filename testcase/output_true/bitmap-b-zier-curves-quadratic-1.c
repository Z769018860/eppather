void quad_bezier(int img[5], int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b) {
    int t[5];
    int x[5];
    int y[5];
    int i[5];
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        t[0] = i[0] * 200;
        x[0] = (1 - t[0]) * (1 - t[0]) * x1 + 2 * (1 - t[0]) * t[0] * x2 + t[0] * t[0] * x3;
        y[0] = (1 - t[0]) * (1 - t[0]) * y1 + 2 * (1 - t[0]) * t[0] * y2 + t[0] * t[0] * y3;
    }
    return;
}
