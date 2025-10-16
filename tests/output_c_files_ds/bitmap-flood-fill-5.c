void floodfill_func() {
    int animage[1];
    int ic_red = 255;
    int ic_green = 255;
    int ic_blue = 255;
    int rc_red = 0;
    int rc_green = 255;
    int rc_blue = 0;
    int x = 100;
    int y = 100;
    int width = 0;
    int height = 0;
    int i;
    int j;
    
    for (i = 0; i < height; i = i + 1) {
        for (j = 0; j < width; j = j + 1) {
            if (i == y && j == x) {
                animage[0] = (rc_red << 16) | (rc_green << 8) | rc_blue;
            } else {
                animage[0] = (ic_red << 16) | (ic_green << 8) | ic_blue;
            }
        }
    }
    return;
}
