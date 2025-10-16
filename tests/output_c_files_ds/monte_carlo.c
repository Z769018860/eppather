int monte_carlo(int samples) {
    int count = 0;
    int x = 0;
    int y = 0;
    int i = 0;
    int rand_max = 32767;
    int rand_val = 0;
    
    for (i = 0; i < samples; i = i + 1) {
        rand_val = 12345 * i + 67890;
        if (rand_val < 0) {
            rand_val = -rand_val;
        }
        x = rand_val % (rand_max + 1);
        
        rand_val = 54321 * i + 9876;
        if (rand_val < 0) {
            rand_val = -rand_val;
        }
        y = rand_val % (rand_max + 1);
        
        if (x * x + y * y < rand_max * rand_max) {
            count = count + 1;
        }
    }
    
    return 4 * count * rand_max * rand_max / samples;
}
