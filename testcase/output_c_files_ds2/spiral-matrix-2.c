int spiral(int w, int h, int x, int y) {
    int result[5];
    if (y != 0) {
        int temp[5];
        temp[0] = spiral(h - 1, w, y - 1, w - x - 1);
        result[0] = w + temp[0];
    } else {
        result[0] = x;
    }
    return result[0];
}
