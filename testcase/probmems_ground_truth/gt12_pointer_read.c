int probmems_pointer_read(int *p, int flag) {
    int result = 0;
    if (flag > 0) {
        result = p[0];
    } else {
        result = p[1];
    }
    return result;
}
