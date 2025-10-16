int one_of_n(int n) {
    int r[5];
    r[0] = 0;
    for (int i = 1; i < n; i = i + 1) {
        int randmax = 32767 / (i + 1) * (i + 1);
        int rand_val;
        for (rand_val = 12345; rand_val >= randmax; rand_val = 56789) {
        }
        if (rand_val / (randmax / (i + 1)) == 0) {
            r[0] = i;
        }
    }
    return r[0];
}
