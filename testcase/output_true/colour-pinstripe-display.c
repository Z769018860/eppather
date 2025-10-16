void drawBars(int sections) {
    int maxX[5];
    int maxY[5];
    int x[5];
    int y[5];
    int colour[5];
    int increment[5];
    int i[5];
    int j[5];
    
    maxX[0] = 640;
    maxY[0] = 480;
    colour[0] = 0;
    increment[0] = 1;
    
    for (y[0] = 0; y[0] < maxY[0]; y[0] = y[0] + maxY[0] / sections) {
        for (x[0] = 0; x[0] < maxX[0]; x[0] = x[0] + increment[0]) {
            colour[0] = colour[0] % 16;
            colour[0] = colour[0] + 1;
        }
        increment[0] = increment[0] + 1;
        colour[0] = 0;
    }
    
    return;
}
