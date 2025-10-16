int nearest_site(int site[150][2], unsigned char rgb[150][3], int size_x, int size_y, double x, double y) {
    int k;
    int ret = 0;
    double d;
    double dist = 0;
    for (k = 0; k < 150; k = k + 1) {
        double dx = x - site[k][0];
        double dy = y - site[k][1];
        d = dx * dx + dy * dy;
        if (k == 0 || d < dist) {
            dist = d;
            ret = k;
        }
    }
    return ret;
}

int at_edge(int color[307200], int size_x, int size_y, int y, int x) {
    int c = color[y * size_x + x];
    int i;
    int j;
    for (i = y - 1; i <= y + 1; i = i + 1) {
        if (i < 0 || i >= size_y) {
            continue;
        }
        for (j = x - 1; j <= x + 1; j = j + 1) {
            if (j < 0 || j >= size_x) {
                continue;
            }
            if (color[i * size_x + j] != c) {
                return 1;
            }
        }
    }
    return 0;
}

void aa_color(int site[150][2], unsigned char rgb[150][3], int size_x, int size_y, unsigned char pix[3], int y, int x) {
    int i;
    int j;
    int n;
    double r = 0;
    double g = 0;
    double b = 0;
    for (i = 0; i < 4; i = i + 1) {
        double yy = y + 0.25 * i + 0.5;
        for (j = 0; j < 4; j = j + 1) {
            double xx = x + 0.25 * j + 0.5;
            n = nearest_site(site, rgb, size_x, size_y, xx, yy);
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

void gen_map(int site[150][2], unsigned char rgb[150][3], int size_x, int size_y, int nearest[307200], unsigned char buf[921600]) {
    int i;
    int j;
    int k;
    unsigned char *ptr = buf;
    for (i = 0; i < size_y; i = i + 1) {
        for (j = 0; j < size_x; j = j + 1) {
            nearest[i * size_x + j] = nearest_site(site, rgb, size_x, size_y, j, i);
        }
    }
    for (i = 0; i < size_y; i = i + 1) {
        for (j = 0; j < size_x; j = j + 1) {
            if (!at_edge(nearest, size_x, size_y, i, j)) {
                ptr[0] = rgb[nearest[i * size_x + j]][0];
                ptr[1] = rgb[nearest[i * size_x + j]][1];
                ptr[2] = rgb[nearest[i * size_x + j]][2];
            } else {
                aa_color(site, rgb, size_x, size_y, ptr, i, j);
            }
            ptr = ptr + 3;
        }
    }
    for (k = 0; k < 150; k = k + 1) {
        unsigned char color = (rgb[k][0] * 0.25 + rgb[k][1] * 0.6 + rgb[k][2] * 0.15 > 80) ? 0 : 255;
        for (i = site[k][1] - 1; i <= site[k][1] + 1; i = i + 1) {
            if (i < 0 || i >= size_y) {
                continue;
            }
            for (j = site[k][0] - 1; j <= site[k][0] + 1; j = j + 1) {
                if (j < 0 || j >= size_x) {
                    continue;
                }
                ptr = buf + 3 * (i * size_x + j);
                ptr[0] = color;
                ptr[1] = color;
                ptr[2] = color;
            }
        }
    }
    return;
}
