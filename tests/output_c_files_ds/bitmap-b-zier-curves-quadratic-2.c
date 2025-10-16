void quad_bezier(int img, int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b) {
    int pts[21][2];
    int i;
    int j;
    double t;
    double a;
    double b_val;
    double c;
    double x;
    double y;
    
    for (i = 0; i <= 20; i = i + 1) {
        t = (double)i / 20.0;
        a = (1.0 - t) * (1.0 - t);
        b_val = 2.0 * t * (1.0 - t);
        c = t * t;
        x = a * (double)x1 + b_val * (double)x2 + c * (double)x3;
        y = a * (double)y1 + b_val * (double)y2 + c * (double)y3;
        pts[i][0] = (int)x;
        pts[i][1] = (int)y;
    }
    
    for (i = 0; i < 20; i = i + 1) {
        j = i + 1;
        int x0 = pts[i][0];
        int y0 = pts[i][1];
        int x1_val = pts[j][0];
        int y1_val = pts[j][1];
    }
    
    return;
}
