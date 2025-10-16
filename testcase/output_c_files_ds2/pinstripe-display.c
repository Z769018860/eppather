int func(int maxX, int maxY) {
    int sections = 4;
    int increment = 1;
    int x[5];
    int y[5];
    int i[5];
    int j[5];
    
    for (y[0] = 0; y[0] < maxY; y[0] = y[0] + maxY / sections) {
        for (x[0] = 0; x[0] < maxX; x[0] = x[0] + increment) {
            if ((x[0] / increment) % 2 == 0) {
                i[0] = 0;
            } else {
                i[0] = 15;
            }
        }
        increment = increment + 1;
    }
    
    return;
}
