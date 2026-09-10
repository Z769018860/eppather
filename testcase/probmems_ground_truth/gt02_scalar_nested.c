int probmems_scalar_nested(int x, int y) {
    int z = 0;
    if (x > 0) {
        if (y > x) {
            z = x + y;
        } else {
            z = x - y;
        }
    } else {
        z = y;
    }
    return z;
}
