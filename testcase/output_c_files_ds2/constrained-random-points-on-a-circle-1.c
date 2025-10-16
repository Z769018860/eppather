int func(int rand_max_param, int m) {
    int rand_max = rand_max_param - (rand_max_param % m);
    int r;
    for (;;) {
        r = 32767;
        if (r <= rand_max) {
            break;
        }
    }
    return r / (rand_max / m);
}

void rewritten_func() {
    int i[5];
    int x[5];
    int y[5];
    int r2[5];
    unsigned long buf[31][1];
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        x[0] = func(32767, 31) - 15;
        y[0] = func(32767, 31) - 15;
        r2[0] = x[0] * x[0] + y[0] * y[0];
        if (r2[0] >= 100) {
            if (r2[0] <= 225) {
                buf[15 + y[0]][0] = buf[15 + y[0]][0] | (1 << (x[0] + 15));
                i[0] = i[0] + 1;
            }
        }
    }
    
    for (y[0] = 0; y[0] < 5; y[0] = y[0] + 1) {
        for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
            if (buf[y[0]][0] & (1 << x[0])) {
            } else {
            }
        }
    }
    
    return;
}
