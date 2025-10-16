void minmax(int x[10], int y[10], int minx[1], int maxx[1], int miny[1], int maxy[1], int n) {
    minx[0] = x[0];
    maxx[0] = x[0];
    miny[0] = y[0];
    maxy[0] = y[0];
    for (int i = 1; i < n; i = i + 1) {
        if (x[i] < minx[0]) {
            minx[0] = x[i];
        }
        if (x[i] > maxx[0]) {
            maxx[0] = x[i];
        }
        if (y[i] < miny[0]) {
            miny[0] = y[i];
        }
        if (y[i] > maxy[0]) {
            maxy[0] = y[i];
        }
    }
    return;
}
