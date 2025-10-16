void WuDrawLine(int x0[5], int y0[5], int x1[5], int y1[5]) {
    int steep[5];
    steep[0] = (y1[0] - y0[0] > x1[0] - x0[0]) ? (y1[0] - y0[0]) : -(y1[0] - y0[0]) > (x1[0] - x0[0] > 0 ? x1[0] - x0[0] : -(x1[0] - x0[0]));
    if (steep[0]) {
        int temp[5];
        temp[0] = x0[0];
        x0[0] = y0[0];
        y0[0] = temp[0];
        temp[0] = x1[0];
        x1[0] = y1[0];
        y1[0] = temp[0];
    }
    if (x0[0] > x1[0]) {
        int temp[5];
        temp[0] = x0[0];
        x0[0] = x1[0];
        x1[0] = temp[0];
        temp[0] = y0[0];
        y0[0] = y1[0];
        y1[0] = temp[0];
    }

    int dx[5];
    dx[0] = x1[0] - x0[0];
    int dy[5];
    dy[0] = y1[0] - y0[0];
    int gradient[5];
    gradient[0] = (dx[0] == 0) ? 1 : dy[0] / dx[0];

    int xpx11[5];
    int intery[5];
    {
        int xend[5];
        xend[0] = x0[0] + (x0[0] > 0 ? 0.5 : -0.5);
        int yend[5];
        yend[0] = y0[0] + gradient[0] * (xend[0] - x0[0]);
        int xgap[5];
        xgap[0] = 1 - (x0[0] - (int)(x0[0]));
        xpx11[0] = (int)(xend[0]);
        int ypx11[5];
        ypx11[0] = (int)(yend[0]);
        intery[0] = yend[0] + gradient[0];
    }

    int xpx12[5];
    {
        int xend[5];
        xend[0] = x1[0] + (x1[0] > 0 ? 0.5 : -0.5);
        int yend[5];
        yend[0] = y1[0] + gradient[0] * (xend[0] - x1[0]);
        int xgap[5];
        xgap[0] = 1 - (x1[0] - (int)(x1[0]));
        xpx12[0] = (int)(xend[0]);
    }

    if (steep[0]) {
        for (int x[5] = {xpx11[0] + 1}; x[0] < xpx12[0]; x[0] = x[0] + 1) {
            intery[0] = intery[0] + gradient[0];
        }
    } else {
        for (int x[5] = {xpx11[0] + 1}; x[0] < xpx12[0]; x[0] = x[0] + 1) {
            intery[0] = intery[0] + gradient[0];
        }
    }
    return;
}
