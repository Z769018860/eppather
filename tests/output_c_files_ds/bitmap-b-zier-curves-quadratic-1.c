void quad_bezier(int img[100][100][3], int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b) {
    int i;
    int j;
    int t;
    int x;
    int y;
    for (t = 0; t <= 1000; t = t + 1) {
        x = (1000 - t) * (1000 - t) * x1 / 1000000 + 2 * (1000 - t) * t * x2 / 1000000 + t * t * x3 / 1000000;
        y = (1000 - t) * (1000 - t) * y1 / 1000000 + 2 * (1000 - t) * t * y2 / 1000000 + t * t * y3 / 1000000;
        if (x >= 0 && x < 100 && y >= 0 && y < 100) {
            img[x][y][0] = r;
            img[x][y][1] = g;
            img[x][y][2] = b;
        }
    }
    return;
}
