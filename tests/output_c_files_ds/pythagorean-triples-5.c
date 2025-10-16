void new_tri(unsigned long in[3], unsigned long* total, unsigned long* prim, unsigned long max_peri) {
    unsigned long t[3];
    unsigned long x = in[0];
    unsigned long y = in[1];
    unsigned long z = in[2];
    unsigned long p;

    for (;;) {
        p = x + y + z;
        if (p > max_peri) {
            return;
        }

        *prim = *prim + 1;
        *total = *total + max_peri / p;

        t[0] = x - 2 * y + 2 * z;
        t[1] = 2 * x - y + 2 * z;
        t[2] = t[1] - y + z;
        new_tri(t, total, prim, max_peri);

        t[0] = t[0] + 4 * y;
        t[1] = t[1] + 2 * y;
        t[2] = t[2] + 4 * y;
        new_tri(t, total, prim, max_peri);

        z = t[2] - 4 * x;
        y = t[1] - 4 * x;
        x = t[0] - 2 * x;
    }
    return;
}
