int filter(int* im, int width, int height, int* K, int Ks, int divisor, int offset, int* oi) {
    int ix;
    int iy;
    int l;
    int kx;
    int ky;
    int cp[3];
    int K_size;
    int x;
    int y;
    int pixel_value;
    int K_index;
    
    K_size = Ks * 2 + 1;
    for (ix = 0; ix < width; ix = ix + 1) {
        for (iy = 0; iy < height; iy = iy + 1) {
            cp[0] = 0;
            cp[1] = 0;
            cp[2] = 0;
            for (kx = -Ks; kx <= Ks; kx = kx + 1) {
                for (ky = -Ks; ky <= Ks; ky = ky + 1) {
                    x = ix + kx;
                    y = iy + ky;
                    if (x < 0 || x >= width || y < 0 || y >= height) {
                        pixel_value = 0;
                    } else {
                        pixel_value = im[x + y * width];
                    }
                    K_index = (kx + Ks) + (ky + Ks) * K_size;
                    for (l = 0; l < 3; l = l + 1) {
                        cp[l] = cp[l] + ((K[K_index] / divisor) * pixel_value + offset);
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
            }
            oi[ix + iy * width] = (cp[0] << 16) | (cp[1] << 8) | cp[2];
        }
    }
    return;
}
