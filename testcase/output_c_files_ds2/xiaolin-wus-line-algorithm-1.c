void draw_line_antialias(int img[5], int x0, int y0, int x1, int y1, int r, int g, int b) {
    int dx[5];
    int dy[5];
    int sx[5];
    int sy[5];
    int err[5];
    int e2[5];
    int x2[5];
    int y2[5];
    int ed[5];
    int i[5];
    
    dx[0] = x1 - x0;
    if (dx[0] < 0) {
        dx[0] = -dx[0];
    }
    
    dy[0] = y1 - y0;
    if (dy[0] < 0) {
        dy[0] = -dy[0];
    }
    
    if (x0 < x1) {
        sx[0] = 1;
    } else {
        sx[0] = -1;
    }
    
    if (y0 < y1) {
        sy[0] = 1;
    } else {
        sy[0] = -1;
    }
    
    if (dx[0] > dy[0]) {
        err[0] = dx[0];
    } else {
        err[0] = -dy[0];
    }
    
    err[0] = err[0] / 2;
    ed[0] = 1;
    
    if (dx[0] + dy[0] == 0) {
        ed[0] = 1;
    } else {
        ed[0] = dx[0] + dy[0];
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        e2[0] = err[0];
        x2[0] = x0;
        y2[0] = y0;
        
        if (2 * e2[0] >= -dx[0]) {
            if (x0 == x1) {
                break;
            }
            if (e2[0] + dy[0] < ed[0]) {
                err[0] = err[0] + dy[0];
                x0 = x0 + sx[0];
            }
        }
        
        if (2 * e2[0] <= dy[0]) {
            if (y0 == y1) {
                break;
            }
            if (dx[0] - e2[0] < ed[0]) {
                err[0] = err[0] - dx[0];
                y0 = y0 + sy[0];
            }
        }
    }
    
    return;
}
