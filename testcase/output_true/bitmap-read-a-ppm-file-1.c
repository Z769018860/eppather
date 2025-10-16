int get_ppm(int pf) {
    int image[5];
    int width[5];
    int height[5];
    int maxval[5];
    int i;
    int j;
    int k;
    
    for (i = 0; i < 5; i = i + 1) {
        width[i] = 0;
        height[i] = 0;
        maxval[i] = 0;
        image[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 5; k = k + 1) {
                image[0] = image[0] + 1;
            }
        }
    }
    
    return;
}
