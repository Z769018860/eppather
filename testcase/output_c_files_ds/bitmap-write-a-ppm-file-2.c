int func() {
    int x;
    int y;
    int x_max = 100;
    int y_max = 100;
    int data[100][100];
    int MaxColorComponentValue = 255;

    for (y = 0; y < y_max; y = y + 1) {
        for (x = 0; x < x_max; x = x + 1) {
            data[y][x] = (x + y) & 255;
        }
    }
    return;
}
