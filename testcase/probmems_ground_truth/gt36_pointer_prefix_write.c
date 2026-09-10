int probmems_pointer_prefix_write(int *p, int n) {
    int i = 1;
    while ((i < n) && (i < 5)) {
        p[i] = p[i] + p[i - 1];
        i = i + 1;
    }
    return p[0];
}
