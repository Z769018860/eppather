void blit_noise(int surf_pixels[76800], int surf_w, int surf_h) {
    int dim;
    int i;
    int temp;
    dim = surf_w * surf_h;
    for (;;) {
        for (i = 0; i < dim; i = i + 1) {
            temp = rand();
            if ((temp & 1) != 0) {
                surf_pixels[i] = 255;
            } else {
                surf_pixels[i] = 0;
            }
        }
        return;
    }
}
