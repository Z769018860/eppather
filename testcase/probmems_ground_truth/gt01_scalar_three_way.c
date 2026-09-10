int probmems_scalar_three_way(int x) {
    int y = 0;
    if (x < 0) {
        y = 1;
    } else {
        if (x == 0) {
            y = 2;
        } else {
            y = 3;
        }
    }
    return y;
}
