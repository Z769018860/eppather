void mouse_move(int maxX, int maxY) {
    int x[5];
    int y[5];
    int factorX[5];
    int factorY[5];
    int ip_type[5];
    int ip_mi_mouseData[5];
    int ip_mi_dx[5];
    int ip_mi_dy[5];
    int ip_mi_dwFlags[5];
    
    x[0] = maxX / 2;
    y[0] = maxY / 2;
    factorX[0] = 65536 / maxX;
    factorY[0] = 65536 / maxY;
    ip_type[0] = 0;
    ip_mi_mouseData[0] = 0;
    ip_mi_dx[0] = 0;
    ip_mi_dy[0] = 0;
    ip_mi_dwFlags[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (x[0] > 5 || y[0] < maxY - 5) {
            ip_mi_mouseData[0] = 0;
            ip_mi_dx[0] = x[0] * factorX[0];
            ip_mi_dy[0] = y[0] * factorY[0];
            ip_mi_dwFlags[0] = 32768 | 1;
            
            if (x[0] > 3) {
                x[0] = x[0] - 1;
            }
            if (y[0] < maxY - 3) {
                y[0] = y[0] + 1;
            }
        }
    }
    
    ip_mi_dwFlags[0] = 32768 | 2 | 4;
    return;
}
