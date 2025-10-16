int gcd_iter(int u, int v) {
    if (u < 0) {
        u = 0 - u;
    }
    if (v < 0) {
        v = 0 - v;
    }
    for (; v != 0; ) {
        u = u % v;
        if (u != 0) {
            v = v % u;
        } else {
            break;
        }
    }
    return u + v;
}
