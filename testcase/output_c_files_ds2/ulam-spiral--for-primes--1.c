int ulam_get_map(int x, int y, int n) {
    int x1 = x - (n - 1) / 2;
    int y1 = y - n / 2;
    int mx = x1 < 0 ? -x1 : x1;
    int my = y1 < 0 ? -y1 : y1;
    int l = mx > my ? 2 * mx : 2 * my;
    int d = y1 >= x1 ? l * 3 + x1 + y1 : l - x1 - y1;
    int l1 = l - 1;
    int result = l1 * l1 + d;
    return result;
}

void output_ulam_spiral(int n, int glyph) {
    int n1 = n % 2 == 0 ? n - 1 : n;
    int b[5];
    int x;
    int y;
    int z;
    int i;
    int j;
    int v = n1 * n1 + 1;
    int b_size = (v >> 6) + 1;
    int b1[5][5];
    int k;
    int m;
    
    for (k = 0; k < 5; k = k + 1) {
        for (m = 0; m < 5; m = m + 1) {
            b1[k][m] = 0;
        }
    }
    
    for (i = 3; i * i <= v; i = i + 2) {
        if (!(b1[i >> 6][0] & (1 << (i >> 1 & 31)))) {
            for (j = i * i; j < v; j = j + (i << 1)) {
                b1[j >> 6][0] = b1[j >> 6][0] | (1 << (j >> 1 & 31));
            }
        }
    }
    
    for (x = 0; x < 5; x = x + 1) {
        for (y = 0; y < 5; y = y + 1) {
            z = ulam_get_map(y, x, n1);
            if (glyph == 0) {
                if (!(b1[z >> 6][0] & (1 << (z >> 1 & 31)))) {
                }
            } else {
            }
        }
    }
    return;
}
