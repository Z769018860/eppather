void output_ppm(int fd, int img_width, int img_height, int img_pixels[100][100][3]) {
    for (int y = 0; y < img_height; y = y + 1) {
        for (int x = 0; x < img_width; x = x + 1) {
            int r = img_pixels[y][x][0];
            int g = img_pixels[y][x][1];
            int b = img_pixels[y][x][2];
        }
    }
    return;
}
