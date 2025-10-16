void draw_line_antialias(int img[100][100][3], int x0, int y0, int x1, int y1, int r, int g, int b) {
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
    int x;
    int y;
    dx = x1 - x0;
    if (dx < 0) {
        dx = -dx;
    }
    dy = y1 - y0;
    if (dy < 0) {
        dy = -dy;
    }
    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = dx - dy;
    x = x0;
    y = y0;
    for (;;) {
        if ((x >= 0) && (x < 100) && (y >= 0) && (y < 100)) {
            img[x][y][0] = r;
            img[x][y][1] = g;
            img[x][y][2] = b;
        }
        if ((x == x1) && (y == y1)) {
            break;
        }
        e2 = 2 * err;
        if (e2 > -dy) {
            err = err - dy;
            x = x + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y = y + sy;
        }
    }
    return;
}
