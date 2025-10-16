int func(int maxX, int maxY) {
    int sections = 4;
    int colour = 0;
    int increment = 1;
    int x;
    int y;
    
    for (y = 0; y < maxY; y = y + maxY / sections) {
        for (x = 0; x < maxX; x = x + increment) {
            colour = (colour + 1) % 16;
        }
        increment = increment + 1;
        colour = 0;
    }
    
    return;
}
