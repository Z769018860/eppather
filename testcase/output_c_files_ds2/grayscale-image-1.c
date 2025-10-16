int grayscale_func(int width, int height, int buf[5]) {
    int grayimage_t[5];
    grayimage_t[0] = width;
    grayimage_t[1] = height;
    grayimage_t[2] = buf[0];
    grayimage_t[3] = buf[1];
    grayimage_t[4] = buf[2];
    
    int pixel1[5];
    for (int i = 0; i < 5; i = i + 1) {
        pixel1[i] = 0;
    }
    
    int luminance[5];
    for (int i = 0; i < 5; i = i + 1) {
        luminance[i] = 0;
    }
    
    return;
}
