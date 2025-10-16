void draw_line_antialias(int img, int x1, int y1, int x2, int y2, int r, int g, int b) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int tmp;
    int x[5];
    int y[5];
    int inter[5];
    int gradient[5];
    int xend[5];
    int yend[5];
    int xgap[5];
    int ygap[5];
    int xpxl1[5];
    int ypxl1[5];
    int xpxl2[5];
    int ypxl2[5];
    int f[5];
    int rf[5];
    
    if (dx < 0) {
        dx = -dx;
    }
    if (dy < 0) {
        dy = -dy;
    }
    
    if (dx > dy) {
        if (x2 < x1) {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        gradient[0] = dy * 1000 / dx;
        xend[0] = x1 + (x1 % 1000 >= 500 ? 1000 - x1 % 1000 : -x1 % 1000);
        yend[0] = y1 * 1000 + gradient[0] * (xend[0] - x1 * 1000) / 1000;
        xgap[0] = 1000 - (x1 * 1000 + 500) % 1000;
        xpxl1[0] = xend[0] / 1000;
        ypxl1[0] = yend[0] / 1000;
        f[0] = yend[0] % 1000;
        rf[0] = 1000 - f[0];
        inter[0] = yend[0] + gradient[0];
        
        xend[1] = x2 + (x2 % 1000 >= 500 ? 1000 - x2 % 1000 : -x2 % 1000);
        yend[1] = y2 * 1000 + gradient[0] * (xend[1] - x2 * 1000) / 1000;
        xgap[1] = (x2 * 1000 + 500) % 1000;
        xpxl2[0] = xend[1] / 1000;
        ypxl2[0] = yend[1] / 1000;
        f[1] = yend[1] % 1000;
        rf[1] = 1000 - f[1];
        
        for (x[0] = xpxl1[0] + 1; x[0] < xpxl2[0]; x[0] = x[0] + 1) {
            f[2] = inter[0] % 1000;
            rf[2] = 1000 - f[2];
            inter[0] = inter[0] + gradient[0];
        }
    } else {
        if (y2 < y1) {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        gradient[0] = dx * 1000 / dy;
        yend[0] = y1 + (y1 % 1000 >= 500 ? 1000 - y1 % 1000 : -y1 % 1000);
        xend[0] = x1 * 1000 + gradient[0] * (yend[0] - y1 * 1000) / 1000;
        ygap[0] = 1000 - (y1 * 1000 + 500) % 1000;
        ypxl1[0] = yend[0] / 1000;
        xpxl1[0] = xend[0] / 1000;
        f[0] = xend[0] % 1000;
        rf[0] = 1000 - f[0];
        inter[0] = xend[0] + gradient[0];
        
        yend[1] = y2 + (y2 % 1000 >= 500 ? 1000 - y2 % 1000 : -y2 % 1000);
        xend[1] = x2 * 1000 + gradient[0] * (yend[1] - y2 * 1000) / 1000;
        ygap[1] = (y2 * 1000 + 500) % 1000;
        ypxl2[0] = yend[1] / 1000;
        xpxl2[0] = xend[1] / 1000;
        f[1] = xend[1] % 1000;
        rf[1] = 1000 - f[1];
        
        for (y[0] = ypxl1[0] + 1; y[0] < ypxl2[0]; y[0] = y[0] + 1) {
            f[2] = inter[0] % 1000;
            rf[2] = 1000 - f[2];
            inter[0] = inter[0] + gradient[0];
        }
    }
    return;
}
