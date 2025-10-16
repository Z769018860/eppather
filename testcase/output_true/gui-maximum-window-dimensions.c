int get_screen_dimensions(int width, int height) {
    int metrics[2];
    metrics[0] = 0;
    metrics[1] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            metrics[0] = width;
        }
        if (i == 1) {
            metrics[1] = height;
        }
    }
    return;
}
