void calc_mandel(int width, int height, int max_iter, int color_rotate, int saturation, int invert) {
    int tex_w[5];
    int tex_h[5];
    int i[5];
    int j[5];
    int iter[5];
    int min[5];
    int max[5];
    int px[5];
    double x[5];
    double y[5];
    double zx[5];
    double zy[5];
    double zx2[5];
    double zy2[5];
    int tex[5][5][3];
    
    min[0] = max_iter;
    max[0] = 0;
    for (i[0] = 0; i[0] < height; i[0] = i[0] + 1) {
        px[0] = 0;
        y[0] = (i[0] - height / 2) * (1.0 / 256) + 0;
        for (j[0] = 0; j[0] < width; j[0] = j[0] + 1) {
            x[0] = (j[0] - width / 2) * (1.0 / 256) + (-0.6);
            iter[0] = 0;
            
            zx[0] = sqrt((x[0] - 0.25) * (x[0] - 0.25) + y[0] * y[0]);
            if (x[0] < zx[0] - 2 * zx[0] * zx[0] + 0.25) {
                iter[0] = max_iter;
            }
            if ((x[0] + 1) * (x[0] + 1) + y[0] * y[0] < 0.0625) {
                iter[0] = max_iter;
            }
            
            zx[0] = 0;
            zy[0] = 0;
            zx2[0] = 0;
            zy2[0] = 0;
            for (; iter[0] < max_iter && zx2[0] + zy2[0] < 4; iter[0] = iter[0] + 1) {
                zy[0] = 2 * zx[0] * zy[0] + y[0];
                zx[0] = zx2[0] - zy2[0] + x[0];
                zx2[0] = zx[0] * zx[0];
                zy2[0] = zy[0] * zy[0];
            }
            if (iter[0] < min[0]) {
                min[0] = iter[0];
            }
            if (iter[0] > max[0]) {
                max[0] = iter[0];
            }
            tex[i[0]][j[0]][0] = iter[0];
            tex[i[0]][j[0]][1] = iter[0];
            tex[i[0]][j[0]][2] = iter[0];
            px[0] = px[0] + 1;
        }
    }
    
    for (i[0] = 0; i[0] < height; i[0] = i[0] + 1) {
        for (j[0] = 0; j[0] < width; j[0] = j[0] + 1) {
            int hue[5];
            hue[0] = tex[i[0]][j[0]][0];
            if (min[0] == max[0]) {
                max[0] = min[0] + 1;
            }
            if (invert) {
                hue[0] = max[0] - (hue[0] - min[0]);
            }
            if (!saturation) {
                tex[i[0]][j[0]][0] = 255 * (max[0] - hue[0]) / (max[0] - min[0]);
                tex[i[0]][j[0]][1] = tex[i[0]][j[0]][0];
                tex[i[0]][j[0]][2] = tex[i[0]][j[0]][0];
                continue;
            }
            double h[5];
            h[0] = fmod(color_rotate + 0.0001 + 4.0 * (hue[0] - min[0]) / (max[0] - min[0]), 6);
            double c[5];
            c[0] = 255 * saturation;
            double X[5];
            X[0] = c[0] * (1 - fabs(fmod(h[0], 2) - 1));
            
            tex[i[0]][j[0]][0] = 0;
            tex[i[0]][j[0]][1] = 0;
            tex[i[0]][j[0]][2] = 0;
            
            if ((int)h[0] == 0) {
                tex[i[0]][j[0]][0] = c[0];
                tex[i[0]][j[0]][1] = X[0];
            } else if ((int)h[0] == 1) {
                tex[i[0]][j[0]][0] = X[0];
                tex[i[0]][j[0]][1] = c[0];
            } else if ((int)h[0] == 2) {
                tex[i[0]][j[0]][1] = c[0];
                tex[i[0]][j[0]][2] = X[0];
            } else if ((int)h[0] == 3) {
                tex[i[0]][j[0]][1] = X[0];
                tex[i[0]][j[0]][2] = c[0];
            } else if ((int)h[0] == 4) {
                tex[i[0]][j[0]][0] = X[0];
                tex[i[0]][j[0]][2] = c[0];
            } else {
                tex[i[0]][j[0]][0] = c[0];
                tex[i[0]][j[0]][2] = X[0];
            }
        }
    }
    return;
}
