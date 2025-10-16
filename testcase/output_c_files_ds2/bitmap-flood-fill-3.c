void floodfill(int img[5], int px, int py, int bankscolor[3], int rcolor[3]) {
    int x[5];
    int y[5];
    int color[3];
    int i;
    int j;
    int k;
    
    for (i = 0; i < 5; i = i + 1) {
        x[i] = 0;
        y[i] = 0;
    }
    
    for (i = 0; i < 3; i = i + 1) {
        color[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 3; k = k + 1) {
                color[k] = img[i];
            }
        }
    }
    
    return;
}
