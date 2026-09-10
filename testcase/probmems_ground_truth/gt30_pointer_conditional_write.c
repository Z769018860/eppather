int probmems_pointer_conditional_write(int *p, int x) {
    if (x > 0) {
        *p = p[1];
    } else {
        *p = p[2];
    }
    return *p;
}
