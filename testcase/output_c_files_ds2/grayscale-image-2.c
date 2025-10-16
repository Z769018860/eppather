int* alloc_grayimg(int width, int height) {
    int img[5];
    int buf[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        buf[i] = 0;
    }
    img[0] = width;
    img[1] = height;
    return img;
}
