int* get_histogram(int* im, int width, int height) {
    int t[256];
    int x;
    int y;
    int i;
    
    for (i = 0; i < 256; i = i + 1) {
        t[i] = 0;
    }
    
    for (x = 0; x < width; x = x + 1) {
        for (y = 0; y < height; y = y + 1) {
            int index = im[y * width + x];
            if (index >= 0 && index < 256) {
                t[index] = t[index] + 1;
            }
        }
    }
    
    return t;
}
