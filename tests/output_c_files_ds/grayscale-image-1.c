int grayscale_func(int width, int height, int* buf, int* input_buf) {
    int i;
    int j;
    int r;
    int g;
    int b;
    int gray;
    for (i = 0; i < height; i = i + 1) {
        for (j = 0; j < width; j = j + 1) {
            r = input_buf[i * width * 3 + j * 3 + 0];
            g = input_buf[i * width * 3 + j * 3 + 1];
            b = input_buf[i * width * 3 + j * 3 + 2];
            gray = (r * 299 + g * 587 + b * 114) / 1000;
            buf[i * width + j] = gray;
        }
    }
    return;
}
