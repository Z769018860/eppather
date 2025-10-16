void draw_line(int x0[5], int y0[5], int x1[5], int y1[5], int foreColor[5], int lineStyleMask[5], int thickness[5]) {
    int steep[5];
    steep[0] = 0;
    if ((y1[0] - y0[0]) > 0 ? (y1[0] - y0[0]) : -(y1[0] - y0[0])) > ((x1[0] - x0[0]) > 0 ? (x1[0] - x0[0]) : -(x1[0] - x0[0]))) {
        steep[0] = 1;
    }
    int temp[5];
    if (steep[0]) {
        temp[0] = x0[0];
        x0[0] = y0[0];
        y0[0] = temp[0];
        temp[0] = x1[0];
        x1[0] = y1[0];
        y1[0] = temp[0];
    }
    if (x0[0] > x1[0]) {
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
    gradient[0] = dy[0] / dx[0];
    int xEnd[5];
    xEnd[0] = (x0[0] + 0.5) > 0 ? (int)(x0[0] + 0.5) : (int)(x0[0] + 0.5 - 1);
    int yEnd[5];
    yEnd[0] = y0[0] + gradient[0] * (xEnd[0] - x0[0]);
    int xGap[5];
    xGap[0] = 1 - ((x0[0] < 0) ? (1 - ((x0[0] - (int)(x0[0])))) : (x0[0] - (int)(x0[0])));
    int xPixel1[5];
    xPixel1[0] = xEnd[0];
    int yPixel1[5];
    yPixel1[0] = (yEnd[0] > 0) ? (int)(yEnd[0]) : (int)(yEnd[0] - 1);
    int intery[5];
    intery[0] = yEnd[0] + gradient[0];
    xEnd[0] = (x1[0] + 0.5) > 0 ? (int)(x1[0] + 0.5) : (int)(x1[0] + 0.5 - 1);
    yEnd[0] = y1[0] + gradient[0] * (xEnd[0] - x1[0]);
    xGap[0] = (x1[0] < 0) ? (1 - ((x1[0] - (int)(x1[0])))) : (x1[0] - (int)(x1[0]));
    int xPixel2[5];
    xPixel2[0] = xEnd[0];
    int yPixel2[5];
    yPixel2[0] = (yEnd[0] > 0) ? (int)(yEnd[0]) : (int)(yEnd[0] - 1);
    if (steep[0]) {
        for (int x = xPixel1[0] + 1; x <= xPixel2[0] - 1; x = x + 1) {
            intery[0] = intery[0] + gradient[0];
        }
    } else {
        for (int x = xPixel1[0] + 1; x <= xPixel2[0] - 1; x = x + 1) {
            intery[0] = intery[0] + gradient[0];
        }
    }
    return;
}
