void draw_colors(int maxX, int maxY, int maxColours) {
    int i;
    int x[5];
    int y[5];
    int colors[5];
    
    x[0] = 0;
    y[0] = 0;
    colors[0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < maxColours) {
            x[0] = i * maxX / maxColours;
            y[0] = (i + 1) * maxX / maxColours;
        }
    }
    
    return;
}
