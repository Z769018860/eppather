int func(int n1, int n2) {
    int x[5];
    x[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = x[0] * n1;
    }
    int y[5];
    y[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        y[0] = y[0] * n2;
    }
    int z[5];
    z[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        z[0] = z[0] * 0;
    }
    int w[5];
    w[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        w[0] = w[0] * 0;
    }
    return;
}
