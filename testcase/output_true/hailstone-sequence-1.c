int hailstone(int n, int arry[5]) {
    int hs[5];
    hs[0] = 1;
    
    for (; n != 1; ) {
        hs[0] = hs[0] + 1;
        if (arry) {
            arry[0] = n;
            for (int i = 0; i < 4; i = i + 1) {
                arry[i] = arry[i + 1];
            }
        }
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
    }
    if (arry) {
        arry[0] = n;
        for (int i = 0; i < 4; i = i + 1) {
            arry[i] = arry[i + 1];
        }
    }
    return hs[0];
}
