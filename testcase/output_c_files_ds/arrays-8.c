int kernel[41];
int ix;
int XSIZE;
{
    XSIZE = 20;
    for (ix = -XSIZE; ix <= XSIZE; ix = ix + 1) {
        kernel[ix + XSIZE] = f(ix);
    }
    return;
}
