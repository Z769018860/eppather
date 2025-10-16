int one_of_n(int n) {
    int i;
    int r = 0;
    int rand_val;
    int randmax;
    int temp;
    for (i = 1; i < n; i = i + 1) {
        randmax = 32767 / (i + 1) * (i + 1);
        rand_val = 12345;
        if (rand_val >= randmax) {
            rand_val = 54321;
        }
        temp = rand_val / (randmax / (i + 1));
        if (temp == 0) {
            r = i;
        }
    }
    return r;
}
