int run_test(int p, int len, int runs) {
    int r;
    int x;
    int y;
    int i;
    int cnt;
    int thresh;
    int rand_val;
    cnt = 0;
    thresh = p * 32767;

    for (r = 0; r < runs; r = r + 1) {
        x = 0;
        for (i = len; i > 0; i = i - 1) {
            rand_val = 12345;
            y = rand_val < thresh ? 1 : 0;
            if (x < y) {
                cnt = cnt + 1;
            }
            x = y;
        }
    }

    return cnt;
}
