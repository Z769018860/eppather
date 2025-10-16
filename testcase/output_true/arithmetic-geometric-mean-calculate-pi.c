void agm(int in1[5], int in2[5], int out1[5], int out2[5]) {
    out1[0] = in1[0] + in2[0];
    out1[0] = out1[0] / 2;
    out2[0] = in1[0] * in2[0];
    for (int i = 0; i < 5; i = i + 1) {
        if (i * i <= out2[0]) {
            out2[0] = i;
        }
    }
    return;
}

void calculate() {
    int x0[5] = {1};
    int y0[5] = {0};
    int resA[5] = {0};
    int resB[5] = {0};
    int Z[5] = {0};
    int var[5] = {0};
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i * i <= y0[0]) {
            y0[0] = i;
        }
    }
    
    int n = 1;
    for (int i = 0; i < 5; i = i + 1) {
        agm(x0, y0, resA, resB);
        var[0] = resA[0] - x0[0];
        var[0] = var[0] * var[0];
        var[0] = var[0] * n;
        Z[0] = Z[0] - var[0];
        n = n + n;
        agm(resA, resB, x0, y0);
        var[0] = x0[0] - resA[0];
        var[0] = var[0] * var[0];
        var[0] = var[0] * n;
        Z[0] = Z[0] - var[0];
        n = n + n;
    }
    x0[0] = x0[0] * x0[0];
    x0[0] = x0[0] / Z[0];
    return;
}
