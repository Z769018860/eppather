void draw(int size) {
    int i;
    int j;
    int k;
    int pix;
    double angle;
    double cx;
    double x;
    double y;
    double d;
    double l;
    double sx[3];
    double sy[3];
    double sw[3];
    double fade[3];
    char shades[11] = " .:-*ca&#%@";
    
    cx = size / 2.0;
    sw[0] = size * 0.02;
    sw[1] = size * 0.03;
    sw[2] = size * 0.05;
    fade[0] = 1.0;
    fade[1] = 0.35;
    fade[2] = 0.35;
    
    for (i = 0; i < size; i = i + 1) {
        y = i - cx;
        for (j = 0; j < size * 2; j = j + 1) {
            x = (j - 2 * cx) / 2;
            pix = 0;
            for (k = 2; k >= 0; k = k - 1) {
                l = (x * sx[k] + y * sy[k]) / (sx[k] * sx[k] + sy[k] * sy[k]);
                if (l > 1) {
                    d = (x - sx[k]) * (x - sx[k]) + (y - sy[k]) * (y - sy[k]);
                } else {
                    if (l >= 0) {
                        d = (x - l * sx[k]) * (x - l * sx[k]) + (y - l * sy[k]) * (y - l * sy[k]);
                    } else {
                        d = x * x + y * y;
                    }
                }
                d = sqrt(d);
                if (d < sw[k] - 0.5) {
                    pix = (int)(10 * fade[k]);
                } else {
                    if (d < sw[k] + 0.5) {
                        pix = (int)((5 + (sw[k] - d) * 10) * fade[k]);
                    }
                }
            }
        }
    }
    return;
}
