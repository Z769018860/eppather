void calc_mandel(int width, int height, int max_iter, int color_rotate, int saturation, int invert, double scale, double cx, double cy, int tex[256][256][3]) {
    int i;
    int j;
    int iter;
    int min;
    int max;
    double x;
    double y;
    double zx;
    double zy;
    double zx2;
    double zy2;
    min = max_iter;
    max = 0;
    for (i = 0; i < height; i = i + 1) {
        y = (i - height / 2) * scale + cy;
        for (j = 0; j < width; j = j + 1) {
            x = (j - width / 2) * scale + cx;
            iter = 0;
            zx = x - 0.25;
            zy = y;
            if (zx * zx + zy * zy < (2 * (zx * zx + zy * zx) - 0.25) * (2 * (zx * zx + zy * zx) - 0.25)) {
                iter = max_iter;
            }
            if ((x + 1) * (x + 1) + y * y < 0.0625) {
                iter = max_iter;
            }
            zx = 0;
            zy = 0;
            zx2 = 0;
            zy2 = 0;
            while (iter < max_iter && zx2 + zy2 < 4) {
                zy = 2 * zx * zy + y;
                zx = zx2 - zy2 + x;
                zx2 = zx * zx;
                zy2 = zy * zy;
                iter = iter + 1;
            }
            if (iter < min) {
                min = iter;
            }
            if (iter > max) {
                max = iter;
            }
            tex[i][j][0] = iter;
            tex[i][j][1] = iter;
            tex[i][j][2] = iter;
        }
    }
    for (i = 0; i < height; i = i + 1) {
        for (j = 0; j < width; j = j + 1) {
            int hue = tex[i][j][0];
            int r;
            int g;
            int b;
            if (min == max) {
                max = min + 1;
            }
            if (invert) {
                hue = max - (hue - min);
            }
            if (!saturation) {
                r = 255 * (max - hue) / (max - min);
                g = r;
                b = r;
            } else {
                double h = (color_rotate + 0.0001 + 4.0 * (hue - min) / (max - min));
                while (h >= 6) {
                    h = h - 6;
                }
                int c = 255 * saturation;
                double X = c * (1 - ((h - 2 * (int)(h / 2)) > 1 ? 2 - (h - 2 * (int)(h / 2)) : (h - 2 * (int)(h / 2))));
                r = 0;
                g = 0;
                b = 0;
                if (h < 1) {
                    r = c;
                    g = X;
                } else if (h < 2) {
                    r = X;
                    g = c;
                } else if (h < 3) {
                    g = c;
                    b = X;
                } else if (h < 4) {
                    g = X;
                    b = c;
                } else if (h < 5) {
                    r = X;
                    b = c;
                } else {
                    r = c;
                    b = X;
                }
            }
            tex[i][j][0] = r;
            tex[i][j][1] = g;
            tex[i][j][2] = b;
        }
    }
    return;
}
