int probmems_pointer_offset_read(int *p, int x) {
    int value = p[1];
    if (x == 0) {
        value = value + p[0];
    } else {
        value = value + p[2];
    }
    return value;
}
