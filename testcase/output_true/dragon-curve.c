void dragon(int leng, int depth) {
    int x[5];
    int y[5];
    int dx[5];
    int dy[5];
    int scale[5];
    int clen[5];
    int tmp[5];
    int i;
    int d;
    int h;
    int w;
    int j;
    int k;
    int buf[5][5];
    int pix[5][5];
    int fpix[5][5][3];
    int maxv[5];
    int dbuf[5][5];

    x[0] = 0;
    y[0] = 0;
    dx[0] = 0;
    dy[0] = 0;
    scale[0] = 0;
    clen[0] = 0;
    tmp[0] = 0;
    d = 0;
    h = 0;
    w = 0;
    maxv[0] = 0;

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            buf[i][j] = 0;
            pix[i][j] = 0;
            dbuf[i][j] = 0;
            for (k = 0; k < 3; k = k + 1) {
                fpix[i][j][k] = 0;
            }
        }
    }

    d = leng / 3 + 1;
    h = leng + 3;
    w = leng + d * 3 / 2 + 2;

    x[0] = d;
    y[0] = d;
    dx[0] = leng;
    dy[0] = 0;
    scale[0] = 1;
    clen[0] = 0;

    for (i = 0; i < depth; i = i + 1) {
        tmp[0] = dx[0] - dy[0];
        dy[0] = dx[0] + dy[0];
        dx[0] = tmp[0];
        scale[0] = scale[0] * 2;
        x[0] = x[0] * 2;
        y[0] = y[0] * 2;
    }

    for (i = 3 * w * h - 1; i >= 0; i = i - 1) {
        if (dbuf[i / (w * h)][(i / h) % w] > maxv[0]) {
            maxv[0] = dbuf[i / (w * h)][(i / h) % w];
        }
    }

    for (i = 3 * h * w - 1; i >= 0; i = i - 1) {
        fpix[i / (w * 3)][(i / 3) % w][i % 3] = 255 * dbuf[i / (w * 3)][(i / 3) % w] / maxv[0];
    }

    return;
}
