int run_test(int p, int len, int runs) {
    int cnt[5] = {0};
    int thresh[5] = {0};
    int r[5] = {0};
    int x[5] = {0};
    int y[5] = {0};
    int i[5] = {0};
    
    thresh[0] = p * 32767;
    
    for (r[0] = 0; r[0] < runs; r[0] = r[0] + 1) {
        for (x[0] = 0, i[0] = len; i[0] > 0; i[0] = i[0] - 1) {
            y[0] = 0;
            if (rand() < thresh[0]) {
                y[0] = 1;
            }
            if (x[0] < y[0]) {
                cnt[0] = cnt[0] + 1;
            }
            x[0] = y[0];
        }
    }
    
    return cnt[0];
}
