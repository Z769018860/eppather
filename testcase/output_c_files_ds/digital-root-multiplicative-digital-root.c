void mdr(int* rmdr, int* rmp, long long n) {
    int r = 0;
    if (n != 0) {
        r = 1;
    }
    while (n != 0) {
        r = r * (n % 10);
        n = n / 10;
    }
    *rmp = *rmp + 1;
    if (r >= 10) {
        mdr(rmdr, rmp, r);
    } else {
        *rmdr = r;
    }
    return;
}
