void fill_img(int img_width, int img_height, int img_buf[5][5][3], int r, int g, int b) {
    int x;
    int y;
    for (x = 0; x < 5; x = x + 1) {
        for (y = 0; y < 5; y = y + 1) {
            img_buf[y][x][0] = r;
            img_buf[y][x][1] = g;
            img_buf[y][x][2] = b;
        }
    }
    return;
}

void put_pixel_unsafe(int img_width, int img_height, int img_buf[5][5][3], int x, int y, int r, int g, int b) {
    img_buf[y][x][0] = r;
    img_buf[y][x][1] = g;
    img_buf[y][x][2] = b;
    return;
}

void put_pixel_clip(int img_width, int img_height, int img_buf[5][5][3], int x, int y, int r, int g, int b) {
    if (x >= 0) {
        if (x < img_width) {
            if (y >= 0) {
                if (y < img_height) {
                    img_buf[y][x][0] = r;
                    img_buf[y][x][1] = g;
                    img_buf[y][x][2] = b;
                }
            }
        }
    }
    return;
}
