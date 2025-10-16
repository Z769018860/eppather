int nearest_site(double site[150][2], double x, double y) {
    int k;
    int ret = 0;
    double d;
    double dist = 0;
    for (k = 0; k < 150; k = k + 1) {
        double dx = x - site[k][0];
        double dy = y - site[k][1];
        d = dx * dx + dy * dy;
        if (k == 0) {
            dist = d;
            ret = k;
        } else {
            if (d < dist) {
                dist = d;
                ret = k;
            }
        }
    }
    return ret;
}

int at_edge(int color[307200], int y, int x) {
    int c = color[y * 640 + x];
    for (int i = y - 1; i <= y + 1; i = i + 1) {
        if (i < 0) {
            continue;
        }
        if (i >= 480) {
            continue;
        }
        for (int j = x - 1; j <= x + 1; j = j + 1) {
            if (j < 0) {
                continue;
            }
            if (j >= 640) {
                continue;
            }
            if (color[i * 640 + j] != c) {
                return 1;
            }
        }
    }
    return 0;
}

void aa_color(unsigned char rgb[150][3], unsigned char pix[3], double site[150][2], int y, int x) {
    double r = 0;
    double g = 0;
    double b = 0;
    for (int i = 0; i < 4; i = i + 1) {
        double yy = y + 1.0 / 4 * i + 0.5;
        for (int j = 0; j < 4; j = j + 1) {
            double xx = x + 1.0 / 4 * j + 0.5;
            int n = nearest_site(site, xx, yy);
            r = r + rgb[n][0];
            g = g + rgb[n][1];
            b = b + rgb[n][2];
        }
    }
    pix[0] = r / 16;
    pix[1] = g / 16;
    pix[2] = b / 16;
    return;
}

void gen_map(double site[150][2], unsigned char rgb[150][3]) {
    int nearest[307200];
    unsigned char buf[921600];
    unsigned char *ptr = buf;
    for (int i = 0; i < 480; i = i + 1) {
        for (int j = 0; j < 640; j = j + 1) {
            nearest[i * 640 + j] = nearest_site(site, j, i);
        }
    }
    for (int i = 0; i < 480; i = i + 1) {
        for (int j = 0; j < 640; j = j + 1) {
            if (at_edge(nearest, i, j) == 0) {
                ptr[0] = rgb[nearest[i * 640 + j]][0];
                ptr[1] = rgb[nearest[i * 640 + j]][1];
                ptr[2] = rgb[nearest[i * 640 + j]][2];
            } else {
                aa_color(rgb, ptr, site, i, j);
            }
            ptr = ptr + 3;
        }
    }
    for (int k = 0; k < 150; k = k + 1) {
        unsigned char color;
        if (rgb[k][0] * 0.25 + rgb[k][1] * 0.6 + rgb[k][2] * 0.15 > 80) {
            color = 0;
        } else {
            color = 255;
        }
        for (int i = site[k][1] - 1; i <= site[k][1] + 1; i = i + 1) {
            if (i < 0) {
                continue;
            }
            if (i >= 480) {
                continue;
            }
            for (int j = site[k][0] - 1; j <= site[k][0] + 1; j = j + 1) {
                if (j < 0) {
                    continue;
                }
                if (j >= 640) {
                    continue;
                }
                ptr = buf + 3 * (i * 640 + j);
                ptr[0] = color;
                ptr[1] = color;
                ptr[2] = color;
            }
        }
    }
    return;
}
