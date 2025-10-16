int mul_inv(int a, int b) {
    int t;
    int nt;
    int r;
    int nr;
    int q;
    int tmp;
    if (b < 0) {
        b = -b;
    }
    if (a < 0) {
        a = b - ((-a) % b);
    }
    t = 0;
    nt = 1;
    r = b;
    nr = a % b;
    for (; nr != 0; ) {
        q = r / nr;
        tmp = nt;
        nt = t - q * nt;
        t = tmp;
        tmp = nr;
        nr = r - q * nr;
        r = tmp;
    }
    if (r > 1) {
        return -1;
    }
    if (t < 0) {
        t = t + b;
    }
    return t;
    return;
}
