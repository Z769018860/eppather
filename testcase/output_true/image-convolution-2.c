int filter(int im_width, int im_height, int Ks, int divisor, int offset, int K[5][5], int im_pixels[5][5][3], int oi_pixels[5][5][3]) {
    int ix;
    int iy;
    int l;
    int kx;
    int ky;
    int cp[3];
    int Ks2;
    int Ks2_plus_1;
    int x;
    int y;
    int pixel_val;
    
    Ks2 = Ks * 2;
    Ks2_plus_1 = Ks2 + 1;
    
    for (ix = 0; ix < 5; ix = ix + 1) {
        for (iy = 0; iy < 5; iy = iy + 1) {
            cp[0] = 0;
            cp[1] = 0;
            cp[2] = 0;
            for (kx = -Ks; kx <= Ks; kx = kx + 1) {
                for (ky = -Ks; ky <= Ks; ky = ky + 1) {
                    x = ix + kx;
                    y = iy + ky;
                    if ((x < 0) || (x >= im_width) || (y < 0) || (y >= im_height)) {
                        pixel_val = 0;
                    } else {
                        pixel_val = im_pixels[x][y][0];
                    }
                    for (l = 0; l < 3; l = l + 1) {
                        cp[l] = cp[l] + ((K[kx + Ks][ky + Ks] / divisor) * pixel_val + offset);
                    }
                }
            }
            for (l = 0; l < 3; l = l + 1) {
                if (cp[l] > 255) {
                    cp[l] = 255;
                } else {
                    if (cp[l] < 0) {
                        cp[l] = 0;
                    }
                }
                oi_pixels[ix][iy][l] = cp[l];
            }
        }
    }
    return;
}
