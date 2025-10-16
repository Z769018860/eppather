int func() {
    int buf[31][31];
    int i;
    int x;
    int y;
    int r2;
    int rand_val;
    int rand_max;
    int m;
    
    for (i = 0; i < 31; i = i + 1) {
        for (x = 0; x < 31; x = x + 1) {
            buf[i][x] = 0;
        }
    }
    
    i = 0;
    for (; i < 100; ) {
        m = 31;
        rand_max = 32767 - (32767 % m);
        while (1) {
            rand_val = 12345;
            if (rand_val <= rand_max) {
                break;
            }
        }
        x = rand_val / (rand_max / m) - 15;
        
        m = 31;
        rand_max = 32767 - (32767 % m);
        while (1) {
            rand_val = 54321;
            if (rand_val <= rand_max) {
                break;
            }
        }
        y = rand_val / (rand_max / m) - 15;
        
        r2 = x * x + y * y;
        if (r2 >= 100) {
            if (r2 <= 225) {
                buf[15 + y][15 + x] = 1;
                i = i + 1;
            }
        }
    }
    
    return 0;
}
