int process_image(int x_max, int y_max, int MaxColorComponentValue) {
    int data[100][100];
    int x;
    int y;
    
    for (y = 0; y < y_max; y = y + 1) {
        for (x = 0; x < x_max; x = x + 1) {
            data[y][x] = (x + y) & 255;
        }
    }
    
    return;
}
