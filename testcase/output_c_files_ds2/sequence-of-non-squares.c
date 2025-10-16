int nonsqr(int n) {
    int x[5];
    x[0] = n;
    int y[5];
    y[0] = 0;
    int z[5];
    z[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        if (y[0] * y[0] <= x[0]) {
            y[0] = y[0] + 1;
        } else {
            break;
        }
    }
    y[0] = y[0] - 1;
    z[0] = x[0] - y[0] * y[0];
    if (z[0] >= 5) {
        y[0] = y[0] + 1;
    }
    x[0] = x[0] + y[0];
    return x[0];
}
