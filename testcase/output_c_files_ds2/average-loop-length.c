int test(int n, int times) {
    int count[5];
    count[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        int x[5];
        x[0] = 1;
        int bits[5];
        bits[0] = 0;
        while (!(bits[0] & x[0])) {
            count[0] = count[0] + 1;
            bits[0] = bits[0] | x[0];
            int r[5];
            r[0] = 32767 / n * n;
            int r1[5];
            r1[0] = 32767;
            while ((r1[0] = 32767) >= r[0]) {
                r1[0] = 32767;
            }
            x[0] = 1 << (r1[0] / (32767 / n));
        }
    }
    return count[0];
}
