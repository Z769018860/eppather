int probmems_pointer_write(int *p, int value) {
    if (value > 0) {
        p[0] = value;
    } else {
        p[1] = 0 - value;
    }
    return p[0];
}
