int move_mouse(int maxX, int maxY) {
    int x = maxX / 2;
    int y = maxY / 2;
    int factorX = 65536 / maxX;
    int factorY = 65536 / maxY;
    int dx;
    int dy;
    int flags;
    
    for (; (x > 5) || (y < maxY - 5); ) {
        dx = x * factorX;
        dy = y * factorY;
        flags = 0x8000 | 0x0001;
        
        if (x > 3) {
            x = x - 1;
        }
        if (y < maxY - 3) {
            y = y + 1;
        }
    }
    
    flags = 0x8000 | 0x0002 | 0x0004;
    return;
}
