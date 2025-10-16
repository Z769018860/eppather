int pi(int tolerance) {
    int x[1000000];
    int y[1000000];
    int val;
    int error;
    int sampled;
    int hit;
    int i;
    int j;
    int temp;
    int rand_max;
    
    rand_max = 32767;
    sampled = 0;
    hit = 0;
    
    for (;;) {
        for (i = 0; i < 1000000; i = i + 1) {
            x[i] = 0;
            y[i] = 0;
            for (j = 0; j < 16; j = j + 1) {
                temp = rand_max;
                x[i] = (x[i] << 1) | (temp & 1);
                temp = rand_max;
                y[i] = (y[i] << 1) | (temp & 1);
            }
            if (x[i] * x[i] + y[i] * y[i] < rand_max * rand_max) {
                hit = hit + 1;
            }
            sampled = sampled + 1;
        }
        
        val = (hit * 4 * 1000000) / sampled;
        temp = val * (1000000 - val) / sampled;
        error = 0;
        for (i = 0; i < 10; i = i + 1) {
            error = (error + temp / error) / 2;
        }
        error = error * 4;
        
        if (hit != 0 && error <= tolerance) {
            break;
        }
    }
    
    return val;
}
