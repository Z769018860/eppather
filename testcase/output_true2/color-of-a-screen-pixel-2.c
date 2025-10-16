int getColorAtCursor(int p_x, int p_y, int hDC, int b) {
    int color[5];
    int p[2];
    p[0] = p_x;
    p[1] = p_y;
    
    if (hDC == 0) {
        color[0] = -1;
        return color[0];
    }
    
    if (b == 0) {
        color[0] = -1;
        return color[0];
    }
    
    color[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        color[0] = color[0] + 1;
    }
    
    return color[0];
}
