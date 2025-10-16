void fill_img_put_pixel(int img_buf[][3], int width, int height, int x, int y, int r, int g, int b, int mode) {
    int i;
    int j;
    if (mode == 0) {
        for (i = 0; i < height; i = i + 1) {
            for (j = 0; j < width; j = j + 1) {
                img_buf[i * width + j][0] = r;
                img_buf[i * width + j][1] = g;
                img_buf[i * width + j][2] = b;
            }
        }
    } else {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            img_buf[y * width + x][0] = r;
            img_buf[y * width + x][1] = g;
            img_buf[y * width + x][2] = b;
        }
    }
    return;
}
