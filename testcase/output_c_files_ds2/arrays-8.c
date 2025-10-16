int func(int ix) {
    int kernel[41];
    int XSIZE = 20;
    int n = 2 * XSIZE + 1;
    int offset = XSIZE;
    int i;
    for (i = 0; i < n; i = i + 1) {
        kernel[i] = 0;
    }
    for (ix = -XSIZE; ix <= XSIZE; ix = ix + 1) {
        kernel[ix + offset] = f(ix);
    }
    return;
}
