void convolution(int* in, int* out, float* kernel, int nx, int ny, int kn, int normalize) {
    int khalf = kn / 2;
    float min = 1000000.0;
    float max = -1000000.0;
    
    if (normalize != 0) {
        for (int m = khalf; m < nx - khalf; m = m + 1) {
            for (int n = khalf; n < ny - khalf; n = n + 1) {
                float pixel = 0.0;
                int c = 0;
                for (int j = -khalf; j <= khalf; j = j + 1) {
                    for (int i = -khalf; i <= khalf; i = i + 1) {
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

    for (int m = khalf; m < nx - khalf; m = m + 1) {
        for (int n = khalf; n < ny - khalf; n = n + 1) {
            float pixel = 0.0;
            int c = 0;
            for (int j = -khalf; j <= khalf; j = j + 1) {
                for (int i = -khalf; i <= khalf; i = i + 1) {
                    pixel = pixel + in[(n - j) * nx + m - i] * kernel[c];
                    c = c + 1;
                }
            }
            if (normalize != 0) {
                pixel = 255 * (pixel - min) / (max - min);
            }
            out[n * nx + m] = (int)pixel;
        }
    }
    return;
}
