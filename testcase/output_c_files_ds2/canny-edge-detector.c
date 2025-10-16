void convolution(int in[5], int out[5], int kernel[5], int nx, int ny, int kn, int normalize) {
    int khalf = kn / 2;
    int min = 2147483647;
    int max = -2147483648;
    int m;
    int n;
    int j;
    int i;
    int c;
    int pixel;

    if (normalize != 0) {
        for (m = khalf; m < nx - khalf; m = m + 1) {
            for (n = khalf; n < ny - khalf; n = n + 1) {
                pixel = 0;
                c = 0;
                for (j = -khalf; j <= khalf; j = j + 1) {
                    for (i = -khalf; i <= khalf; i = i + 1) {
                        pixel = pixel + in[(n - j) * nx + m - i] * kernel[c];
                        c = c + 1;
                    }
                }
                if (pixel < min) {
                    min = pixel;
                }
                if (pixel > max) {
                    max = pixel;
                }
            }
        }
    }

    for (m = khalf; m < nx - khalf; m = m + 1) {
        for (n = khalf; n < ny - khalf; n = n + 1) {
            pixel = 0;
            c = 0;
            for (j = -khalf; j <= khalf; j = j + 1) {
                for (i = -khalf; i <= khalf; i = i + 1) {
                    pixel = pixel + in[(n - j) * nx + m - i] * kernel[c];
                    c = c + 1;
                }
            }
            if (normalize != 0) {
                pixel = 255 * (pixel - min) / (max - min);
            }
            out[n * nx + m] = pixel;
        }
    }
    return;
}
