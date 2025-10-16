int* alloc_grayimg(int width, int height) {
    int* img;
    int buf[10000];
    img = buf;
    img[0] = width;
    img[1] = height;
    return img;
}
