void radix_sort(int a[5], int len) {
    unsigned x[5];
    int i;
    int n1;
    n1 = -2147483648;
    for (i = 0; i < 5; i = i + 1) {
        x[i] = a[i] ^ n1;
    }
    {
        unsigned from[5];
        unsigned to[5];
        unsigned bit;
        int ll;
        int rr;
        unsigned tmp;
        for (i = 0; i < 5; i = i + 1) {
            from[i] = x[i];
            to[i] = x[i];
        }
        bit = n1;
        if (!bit || to[0] < from[0] + 1) {
            ;
        } else {
            ll = from[0];
            rr = to[0] - 1;
            for (;;) {
                while (ll < rr && !(from[ll] & bit)) {
                    ll = ll + 1;
                }
                while (ll < rr && (to[rr] & bit)) {
                    rr = rr - 1;
                }
                if (ll >= rr) {
                    break;
                }
                tmp = from[ll];
                from[ll] = to[rr];
                to[rr] = tmp;
            }
            if (!(bit & from[ll]) && ll < to[0]) {
                ll = ll + 1;
            }
            bit = bit >> 1;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        a[i] = x[i] ^ n1;
    }
    return;
}
