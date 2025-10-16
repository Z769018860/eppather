int ulam_get_map(int x, int y, int n) {
    int temp_x;
    int temp_y;
    int mx;
    int my;
    int l;
    int d;
    temp_x = x - ((n - 1) / 2);
    temp_y = y - (n / 2);
    if (temp_x < 0) {
        mx = -temp_x;
    } else {
        mx = temp_x;
    }
    if (temp_y < 0) {
        my = -temp_y;
    } else {
        my = temp_y;
    }
    if (mx > my) {
        l = 2 * mx;
    } else {
        l = 2 * my;
    }
    if (temp_y >= temp_x) {
        d = l * 3 + temp_x + temp_y;
    } else {
        d = l - temp_x - temp_y;
    }
    return (l - 1) * (l - 1) + d;
}

void output_ulam_spiral(int n, int glyph) {
    int x;
    int y;
    int z;
    int sieve[1024];
    int i;
    int j;
    int k;
    int v;
    int b[16];
    for (i = 0; i < 16; i = i + 1) {
        b[i] = 0;
    }
    v = n * n + 1;
    for (i = 3; i * i <= v; i = i + 2) {
        if (!(b[i >> 6] & (1 << (i >> 1 & 31)))) {
            for (j = i * i; j < v; j = j + (i << 1)) {
                b[j >> 6] = b[j >> 6] | (1 << (j >> 1 & 31));
            }
        }
    }
    if (n % 2 == 0) {
        n = n - 1;
    }
    for (x = 0; x < n; x = x + 1) {
        for (y = 0; y < n; y = y + 1) {
            z = ulam_get_map(y, x, n);
            if (glyph == 0) {
            } else {
            }
        }
    }
    return;
}
