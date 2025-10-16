void func() {
    int x;
    int y;
    int i;
    int SIZE = 16;
    for (y = SIZE - 1; y >= 0; y = y - 1) {
        for (i = 0; i < y; i = i + 1) {
        }
        for (x = 0; x + y < SIZE; x = x + 1) {
            if (x & y) {
            } else {
            }
        }
    }
    return;
}
