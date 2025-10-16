int func() {
    int r;
    int rand_max = 32767 - (32767 % 5);
    for (;;) {
        r = rand();
        if (r < rand_max) {
            break;
        }
    }
    r = r / (rand_max / 5) + 1;
    
    int r2;
    for (;;) {
        r2 = r * 5 + r;
        if (r2 < 27) {
            break;
        }
    }
    r2 = r2 / 3 - 1;
    
    int n = 7;
    int cnt = 1000000;
    double delta = 0.03;
    int bins[7] = {0, 0, 0, 0, 0, 0, 0};
    int i = cnt;
    
    for (; i > 0; i = i - 1) {
        int val = r2;
        bins[val - 1] = bins[val - 1] + 1;
    }
    
    for (i = 0; i < n; i = i + 1) {
        double ratio = bins[i] * n / (double)cnt - 1;
        if (ratio > -delta && ratio < delta) {
            continue;
        }
        break;
    }
    
    return i == n;
}
