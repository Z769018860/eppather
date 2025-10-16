int func(int size) {
    int x[5];
    int y[5];
    int i[5];
    int j[5];
    y[0] = size - 1;
    for (; y[0] >= 0; y[0] = y[0] - 1) {
        i[0] = 0;
        for (; i[0] < y[0]; i[0] = i[0] + 1) {
        }
        x[0] = 0;
        for (; x[0] + y[0] < size; x[0] = x[0] + 1) {
            if (x[0] & y[0]) {
            } else {
            }
        }
    }
    return;
}
