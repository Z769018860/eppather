int spiral(int w, int h, int x, int y) {
    int result;
    if (y != 0) {
        result = w + spiral(h - 1, w, y - 1, w - x - 1);
    } else {
        result = x;
    }
    return result;
}
