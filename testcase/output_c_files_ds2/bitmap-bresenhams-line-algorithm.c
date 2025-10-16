void line(int x0, int y0, int x1, int y1) {
    int dx;
    int sx;
    int dy;
    int sy;
    int err;
    int e2;
    int temp1;
    int temp2;
    
    temp1 = x1 - x0;
    if (temp1 < 0) {
        dx = 0 - temp1;
    } else {
        dx = temp1;
    }
    
    if (x0 < x1) {
        sx = 1;
    } else {
        sx = -1;
    }
    
    temp2 = y1 - y0;
    if (temp2 < 0) {
        dy = 0 - temp2;
    } else {
        dy = temp2;
    }
    
    if (y0 < y1) {
        sy = 1;
    } else {
        sy = -1;
    }
    
    if (dx > dy) {
        err = dx / 2;
    } else {
        err = 0 - dy / 2;
    }
    
    for (;;) {
        if (x0 == x1) {
            if (y0 == y1) {
                break;
            }
        }
        
        e2 = err;
        if (e2 > (0 - dx)) {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 < dy) {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
    
    return;
}
