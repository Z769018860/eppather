int test_combined(int n, int times) {
    int count = 0;
    int i;
    for (i = 0; i < times; i = i + 1) {
        int x = 1;
        int bits = 0;
        int rmax = 32767 / n * n;
        int r;
        for (;;) {
            r = rand();
            if (r < rmax) {
                break;
            }
        }
        int rand_val = r / (32767 / n);
        x = 1;
        bits = 0;
        for (;;) {
            if ((bits & x) != 0) {
                break;
            }
            count = count + 1;
            bits = bits | x;
            for (;;) {
                r = rand();
                if (r < rmax) {
                    break;
                }
            }
            rand_val = r / (32767 / n);
            x = 1;
            int j;
            for (j = 0; j < rand_val; j = j + 1) {
                x = x * 2;
            }
        }
    }
    return count;
}
