int hailstone(int n, int arry[100000]) {
    int hs;
    int i;
    hs = 1;
    for (i = 0; n != 1; i = i + 1) {
        hs = hs + 1;
        if (arry) {
            arry[i] = n;
        }
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
    }
    if (arry) {
        arry[i] = n;
    }
    return hs;
}
