int func() {
    int maxX = 640;
    int maxY = 480;
    int sections = 4;
    int increment = 1;
    int x;
    int y;
    int color;
    
    for (y = 0; y < maxY; y = y + maxY / sections) {
        for (x = 0; x < maxX; x = x + increment) {
            if ((x / increment) % 2 == 0) {
                color = 0;
            } else {
                color = 15;
            }
        }
        increment = increment + 1;
    }
    
    return;
}
